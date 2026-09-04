.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _user_manual_data_types:

####################
Supported data types
####################

This section describes the IDL constructs that |eddsrecorder| supports and how each of them is mapped to the generated
SQL schema.

.. note::

    All of this applies to the ``-queryable`` schema only, since it is the one that deserializes the
    samples into columns. The default schema stores every sample as a raw :term:`CDR` payload and is
    therefore indifferent to the data type; see :ref:`user_manual_monitor_schema`.

.. _user_manual_data_types_basic_types:

***********
Basic types
***********

For each basic type field in a DDS Topic, |eddsrecorder| creates a column in the corresponding topic table using the
same name and a compatible SQLite type.

.. list-table:: IDL to SQLite type mapping (basic types)
    :header-rows: 1
    :widths: 30 30 40

    *   - IDL basic type
        - SQL field type
        - Notes

    *   - ``octet``
        - ``TINYINT``
        -

    *   - ``short``
        - ``SMALLINT``
        -

    *   - ``unsigned short``
        - ``SMALLINT UNSIGNED``
        -

    *   - ``long``
        - ``INT``
        -

    *   - ``unsigned long``
        - ``INT UNSIGNED``
        -

    *   - ``long long``
        - ``BIGINT``
        -

    *   - ``unsigned long long``
        - ``BIGINT UNSIGNED``
        -

    *   - ``char``
        - ``CHARACTER(1)``
        -

    *   - ``string``
        - ``TEXT``
        -

    *   - ``float``
        - ``FLOAT``
        -

    *   - ``double``
        - ``DOUBLE``
        -

    *   - ``boolean``
        - ``TINYINT``
        - Stored as ``0`` or ``1``.

    *   - ``enumeration``
        - ``TEXT``
        - Stored as the name of the |br|
          enumerator, not its ordinal.

.. note::

    SQLite does not enforce column types, so the declared types above act as documentation of the original IDL type
    rather than as a constraint.
    The width of an integer column, for instance, tells you how to interpret the value, but SQLite will happily store
    whatever |eddsrecorder| writes into it.

.. _user_manual_data_types_unsupported:

Unsupported basic types
=======================

The following IDL basic types have no mapping in this release.
A topic whose data type uses one of them is reported on the console as an unrecognized kind and the topic is not
recorded:

* ``long double``
* ``wchar`` and ``wstring``

.. _user_manual_data_types_sequences_arrays:

********************
Sequences and arrays
********************

|eddsrecorder| supports sequences and multidimensional arrays of basic types.

.. note::

    Future releases will include support for sequences and arrays of user types.
    Sequences and arrays of ``string`` are not recorded either: the column is created but the element values are not
    stored.

Because a SQL row cannot hold a variable number of values, these fields are stored out of line.
For each sequence or array, |eddsrecorder| creates:

* An integer column in the topic table named ``<Array/SequenceName>_id``, which links a sample to its elements.
* An auxiliary table named ``<TopicName>_<Array/SequenceName>`` to store the elements themselves, with this schema:

  * ``<Array/SequenceName>_id``: integer column matching the one in the main table.
  * One integer index column per dimension, named ``index_0``, ``index_1``, ... ``index_N``.
    An array declared ``long m[4][3]`` therefore gets ``index_0`` and ``index_1``, while a sequence always gets a
    single ``index_0``.
  * ``value``: the element value, typed according to
    :ref:`the basic type mapping <user_manual_data_types_basic_types>`.

To view the topic samples data including an array or sequence field, an SQL query can be used:

.. code-block:: sql

    SELECT * FROM <TopicName>
        INNER JOIN <TopicName>_<Array/SequenceName>
        ON <TopicName>.<Array/SequenceName>_id = <TopicName>_<Array/SequenceName>.<Array/SequenceName>_id;

Example
=======

Consider a ``Foo`` topic with the following data type:

.. code-block:: idl

    struct Foo_Type {
        long myId;
        long myArray[10];
    };

|eddsrecorder| would generate the following tables:

.. list-table::
    :header-rows: 1

    *   - ``Data_Foo``
        - ``Data_Foo_myArray``

    *   - ``writer_guid`` |br|
          ``sequence_number`` |br|
          ``myId``
        - ``writer_guid`` |br|
          ``sequence_number`` |br|
          ``index_0`` |br|
          ``value``

Each ``Foo`` sample produces one row in ``Data_Foo`` and ten rows in ``Data_Foo_myArray``, with ``index_0`` running
from ``0`` to ``9``.
Both tables carry the same key, so the values of ``myArray`` for a given sample are read by joining on it:

.. code-block:: sql

    SELECT e.index_0, e.value
      FROM Data_Foo_myArray e
     WHERE e.writer_guid = :guid AND e.sequence_number = :seq
     ORDER BY e.index_0;

.. _user_manual_data_types_internal_structures:

*******************
Internal Structures
*******************

Nested structures are flattened into the topic table.
|eddsrecorder| creates a column for each field of the inner structure, prefixing the field name with the inner
structure member name:

.. code-block:: text

    <InnerStructureName>_<FieldName>

The prefixes accumulate, so a member nested two levels deep yields
``<OuterMemberName>_<InnerMemberName>_<FieldName>``.
A variable length field inside a nested structure follows the same rule: its auxiliary table is named
``Data_<TopicName>_<InnerStructureName>_<FieldName>``.

Example
=======

Consider the following IDL:

.. code-block:: idl

    struct MyInnerStruct {
        long counter;
        string message;
    };

    struct MyStruct {
        long id;
        MyInnerStruct myIS;
    }; /* This is the type we will use for the topic */

|eddsrecorder| creates the following fields for the topic table:

.. list-table:: Inner structure example - topic fields
    :header-rows: 1

    *   - Table field
        - Field type

    *   - ``writer_guid``
        - ``TEXT``

    *   - ``sequence_number``
        - ``INTEGER``

    *   - ``id``
        - ``INT``

    *   - ``myIS_counter``
        - ``INT``

    *   - ``myIS_message``
        - ``TEXT``

.. _user_manual_data_types_unions:

******
Unions
******

A union is flattened much like a nested structure: |eddsrecorder| creates a column for each member of the union,
prefixing the member name with the union member name:

.. code-block:: text

    <UnionName>_<FieldName>

It also creates a discriminator column:

.. code-block:: text

    <UnionName>_discriminator

The discriminator holds the value that selected the active member for that sample, so it is the column to read to know
which of the other columns is meaningful.
The columns belonging to the members that were not selected are set to ``NULL``.

Example
=======

Consider the following IDL:

.. code-block:: idl

    union MyUnion switch (long /* discriminator type */) {
        case 1:
            long counter;
        case 2:
            string message;
    };

    struct MyStruct {
        long id;
        MyUnion myU;
    }; /* This is the type we will use for the topic */

|eddsrecorder| creates the following fields for the topic table:

.. list-table:: Union example - topic fields
    :header-rows: 1

    *   - Table field
        - Field type

    *   - ``writer_guid``
        - ``TEXT``

    *   - ``sequence_number``
        - ``INTEGER``

    *   - ``id``
        - ``INT``

    *   - ``myU_discriminator``
        - ``INT``

    *   - ``myU_counter``
        - ``INT``

    *   - ``myU_message``
        - ``TEXT``

A sample carrying ``counter`` is stored with ``myU_discriminator`` set to ``1``, ``myU_counter`` set to the value, and
``myU_message`` set to ``NULL``.
Selecting only the samples that used a given branch is therefore a matter of filtering on the discriminator:

.. code-block:: sql

    SELECT sequence_number, myU_counter FROM Data_MyTopic WHERE myU_discriminator = 1;
