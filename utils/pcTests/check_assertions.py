#!/usr/bin/env python3
"""Check that every assertion in check_monitor_schema.py can actually fail.

The regression suite once contained this:

    checker.check('%s: MessagesCapture never loses a transmission' % name,
                  expected_captures >= expected_messages)

Both operands were constants from a dict, so the assertion could never fail whatever the recorder
produced, and a real defect went unnoticed behind a passing check.  This script exists so that
does not happen again: it parses check_monitor_schema.py and reports any assertion whose outcome
cannot depend on a recording.

An assertion counts as backed by a recording when either of its operands mentions something that
came out of one: a call to query(), one(), tables(), views(), indices(), packets(), errors() or
exit_status(), or a name assigned from such a call, directly or through a comprehension.  A literal False is not an
assertion but a report, reached only when a guard above it has already failed, so it is skipped.

Names are tracked per function, not across the file.  Two functions may use the same variable
name for unrelated things -- `missing` holds table names read from a database in one and file
names read from the filesystem in another -- and treating them as one would let a vacuous
assertion hide behind an unrelated function's variable.

A handful of assertions legitimately check something other than a recording.  They are listed in
ALLOWED with the reason, and the list is required to stay exact: an unlisted assertion fails the
run, and so does a listed one that no longer exists.

Standard library only.  Reads the file; it never runs the recorder, so it costs nothing.
"""

import argparse
import ast
import os
import sys

REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
TARGET = os.path.join(REPO, 'utils', 'pcTests', 'check_monitor_schema.py')

# Calls whose result can only have come from a recorded database or the recorder's own output.
OBSERVED_CALLS = {'query', 'one', 'tables', 'views', 'indices', 'packets', 'errors',
                  'exit_status'}

# Assertions that deliberately check something else, keyed by the literal text of their label.
ALLOWED = {
    'the fixture files are present: %s':
        'checks the repository layout rather than a recording. Every fixture is committed, so a '
        'missing one is a failure; asserting it here is what stops the suite from quietly '
        'testing less than it appears to',
}


class Tracker(ast.NodeVisitor):
    """Collects the names that hold something read back from a recording."""

    def __init__(self):
        self.observed = set()

    def visit_Assign(self, node):
        if self.uses_observed(node.value):
            self.bind(node.targets)
        self.generic_visit(node)

    def visit_AugAssign(self, node):
        if self.uses_observed(node.value):
            self.bind([node.target])
        self.generic_visit(node)

    def visit_For(self, node):
        if self.uses_observed(node.iter):
            self.bind([node.target])
        self.generic_visit(node)

    def bind(self, targets):
        for target in targets:
            for node in ast.walk(target):
                if isinstance(node, ast.Name):
                    self.observed.add(node.id)

    def uses_observed(self, node):
        for sub in ast.walk(node):
            if isinstance(sub, ast.Call):
                function = sub.func
                if isinstance(function, ast.Name) and function.id in OBSERVED_CALLS:
                    return True
                if isinstance(function, ast.Attribute) and function.attr in OBSERVED_CALLS:
                    return True
            if isinstance(sub, ast.Name) and sub.id in self.observed:
                return True
        return False


def track(tree):
    """Runs the tracker until the set of observed names stops growing.

    Repeated because a name may be assigned after the assertion that reads it, and because one
    assignment can make another observed in turn.
    """
    tracker = Tracker()

    while True:
        before = len(tracker.observed)
        tracker.visit(tree)

        # Comprehension and generator targets, which are expressions rather than statements.
        for node in ast.walk(tree):
            if isinstance(node, (ast.ListComp, ast.SetComp, ast.GeneratorExp, ast.DictComp)):
                for generator in node.generators:
                    if tracker.uses_observed(generator.iter):
                        tracker.bind([generator.target])

        if len(tracker.observed) == before:
            return tracker


def assertions(tree):
    """Yields every checker.check / checker.equal call in the file."""
    for node in ast.walk(tree):
        if not isinstance(node, ast.Call):
            continue
        function = node.func
        if (isinstance(function, ast.Attribute)
                and function.attr in ('check', 'equal')
                and isinstance(function.value, ast.Name)
                and function.value.id == 'checker'):
            yield node


def label_text(node):
    """The literal part of an assertion's label, used to identify it."""
    if not node.args:
        return '<no label>'
    for sub in ast.walk(node.args[0]):
        if isinstance(sub, ast.Constant) and isinstance(sub.value, str):
            return sub.value
    return ast.unparse(node.args[0])


def main(argv=None):
    parser = argparse.ArgumentParser(
        description='Check that every assertion in the regression suite can fail.')
    parser.add_argument('-t', '--target', default=TARGET,
                        help='file to check (default: utils/pcTests/check_monitor_schema.py)')
    parser.add_argument('-v', '--verbose', action='store_true',
                        help='list every assertion and whether it reads a recording')
    args = parser.parse_args(argv)

    if not os.path.exists(args.target):
        print('error: %s not found' % args.target, file=sys.stderr)
        return 2

    tree = ast.parse(open(args.target).read())

    total = 0
    unbacked = []
    allowed_seen = set()

    # Each function gets its own set of observed names, so a variable in one cannot vouch for a
    # same-named variable in another.
    scopes = [node for node in ast.walk(tree) if isinstance(node, ast.FunctionDef)]
    seen_here = set()

    for scope in scopes:
        tracker = track(scope)

        for node in assertions(scope):
            if id(node) in seen_here:
                continue
            seen_here.add(id(node))
            total += 1
            operands = node.args[1:3]
            label = label_text(node)

            if any(tracker.uses_observed(operand) for operand in operands):
                if args.verbose:
                    print('  reads db   %s' % label)
                continue

            condition = node.args[1] if len(node.args) > 1 else None
            if isinstance(condition, ast.Constant) and condition.value is False:
                # A report, not an assertion: reached once a guard above it has failed.
                if args.verbose:
                    print('  reports    %s' % label)
                continue

            if label in ALLOWED:
                allowed_seen.add(label)
                if args.verbose:
                    print('  allowed    %s' % label)
                continue

            unbacked.append((node.lineno, label,
                             ' , '.join(ast.unparse(operand) for operand in operands)))

    stray = [n for n in assertions(tree) if id(n) not in seen_here]
    for node in stray:
        total += 1
        unbacked.append((node.lineno, label_text(node), 'assertion outside any function'))

    shown = os.path.relpath(args.target, REPO)
    if shown.startswith(os.pardir):
        shown = args.target
    print('%s: %d assertion(s)' % (shown, total))

    stale = sorted(set(ALLOWED) - allowed_seen)
    failed = False

    for line, label, operands in unbacked:
        failed = True
        print('  FAIL line %d: this assertion cannot fail' % line)
        print('       label:    %s' % label)
        print('       operands: %s' % operands)
        print('       Make it compare something read back from the recording, or add it to '
              'ALLOWED in this script with the reason.')

    for label in stale:
        failed = True
        print('  FAIL ALLOWED lists an assertion that is no longer there: %s' % label)
        print('       Remove the entry so the list keeps meaning something.')

    if failed:
        return 1

    print('OK: %d backed by a recording, %d allowed' % (total - len(allowed_seen),
                                                        len(allowed_seen)))
    return 0


if __name__ == '__main__':
    sys.exit(main())
