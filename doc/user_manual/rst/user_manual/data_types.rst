.. include:: ../exports/alias.include
.. include:: ../exports/roles.include

.. _user_manual_data_types:

####################
Supported data types
####################

This section describes the data types that |eddsrecorder| supports and how the data is stored.

.. _user_manual_data_types_basic_types:

***********
Basic types
***********

For each basic type field in a DDS Topic, |eddsrecorder| creates a field in the corresponding topic table using the
same name and a compatible SQLite type.

.. list-table:: IDL to SQLite type mapping (basic types)
    :header-rows: 1

    *   - IDL basic type
        - SQL field type

    *   - ``octet``
        - ``TINYINT``

    *   - ``short``
        - ``SMALLINT``

    *   - ``unsigned short``
        - ``SMALLINT UNSIGNED``

    *   - ``long``
        - ``INT``

    *   - ``unsigned long``
        - ``INT UNSIGNED``

    *   - ``long long``
        - ``BIGINT``

    *   - ``unsigned long long``
        - ``BIGINT UNSIGNED``

    *   - ``char``
        - ``CHARACTER(1)``

    *   - ``string``
        - ``TEXT``

    *   - ``float``
        - ``FLOAT``

    *   - ``double``
        - ``DOUBLE``

    *   - ``boolean``
        - ``TINYINT``

    *   - ``enumeration``
        - ``TEXT``

.. _user_manual_data_types_sequences_arrays:

********************
Sequences and arrays
********************

|eddsrecorder| supports sequences and multidimensional arrays of basic types.

.. note::

    Future releases will include support for sequences and arrays of user types.

For each sequence or array, |eddsrecorder| creates:

* An integer field in the topic table named ``<Array/SequenceName>_id``.
* An auxiliary table named ``<TopicName>_<Array/SequenceName>`` to store the array or sequence data.
  The table schema is:

  * The ``<Array/SequenceName>_id`` integer field to identify the array or sequence.
  * A set of integer fields named ``<index_n>`` for the array or sequence indexes.
  * The fields for the data.

To view the topic samples data including an array or sequence field, an SQL query can be used:

.. code-block:: sql

    select * from <TopicName>
        inner join <TopicName>_<Array/SequenceName>
        on <TopicName>.<Array/SequenceName>_id = <TopicName>_<Array/SequenceName>.<Array/SequenceName>_id;

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

    *   - ``Foo``
        - ``Foo_myArray``

    *   - ``message_id`` |br|
          MetaData fields |br|
          ``myId`` |br|
          ``myArray_id``
        - ``myArray_id`` |br|
          ``index_0`` |br|
          ``value``

To get the values of ``myArray`` for a given ``Foo`` sample the following query can be performed:

.. code-block:: sql

    select Foo_myArray.* from Foo
        inner join Foo_myArray on Foo.myArray_id = Foo_myArray.myArray_id
    where
        Foo.message_id = <a_Valid_Id>;

.. _user_manual_data_types_internal_structures:

*******************
Internal Structures
*******************

In the case of internal structures, |eddsrecorder| creates a new field in the topic table for each field in the inner
structure, prefixing the field name with the inner structure name:

.. code-block:: text

    <InnerStructureName>_<FieldName>

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

    *   - ``message_id``
        - ``INT``

    *   - MetaData fields
        - ...

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

|eddsrecorder| creates a new field in the topic table for each field in the union, prefixing the field name with the
union name:

.. code-block:: text

    <UnionName>_<FieldName>

It also creates a discriminator field for the union:

.. code-block:: text

    <UnionName>_discriminator

The discriminator specifies the union field used for a sample.

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

    *   - ``message_id``
        - ``INT``

    *   - MetaData fields
        - ...

    *   - ``id``
        - ``INT``

    *   - ``myU_discriminator``
        - ``INT``

    *   - ``myU_counter``
        - ``INT``

    *   - ``myU_message``
        - ``TEXT``
