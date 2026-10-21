# eProsima Non-Intrusive DDS Recorder docs

This package generates the *eProsima Non-Intrusive DDS Recorder* documentation.
This package is powered by [sphinx](https://www.sphinx-doc.org/en/master/) and is meant to be deployed in
[readthedocs](https://readthedocs.org/).

The content of this documentation is the ReadTheDocs version of the manuals distributed with the product in
`doc/pdf`: *Installation Manual*, *User Manual* and *Release Notes*.

---

## Documentation generation

### Dependencies

Before being able to build the documentation, some dependencies need to be installed:

```bash
sudo apt update
sudo apt install -y \
    python3 \
    python3-pip \
    python3-venv \
    python3-sphinxcontrib.spelling \
    imagemagick
pip3 install -U -r doc/user_manual/requirements.txt
```

### Build documentation

The documentation can be built directly with sphinx from this directory:

```bash
sphinx-build -b html . _build/html
```

Alternatively, if the [cmake_utils](https://github.com/eProsima/dev-utils) package is available in the workspace, the
package can be built with colcon:

```bash
colcon build --packages-select ddsrecorder_docs
```

In order to compile and execute the package **tests**, a specific CMake option is required: `BUILD_DOCS_TESTS`.

```bash
colcon build --packages-select ddsrecorder_docs --cmake-args -DBUILD_DOCS_TESTS=ON
colcon test --packages-select ddsrecorder_docs --event-handler console_direct+
```

---

## Documentation structure

This documentation is focused on the user manual for installing and working with the
*eProsima Non-Intrusive DDS Recorder*:

* **Installation Manual**: basic requirements and installation instructions for Windows and Linux.
* **User Manual**: introduction, capturing DDS traffic, command line usage, structure of the generated database,
  supported data types, SQL recipes to query a recording, and the limitations of the current release.
* **Release Notes**: system requirements, supported databases, supported DDS implementations and supported capture
  formats.
* **Appendixes**: glossary of the nomenclature used throughout the documentation.
