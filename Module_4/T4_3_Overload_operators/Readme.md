**Objective:** Learning to overload arithmetic and relational operators.

In this exercise, we continue with the class ``GeomVector`` that was used as an example before. 
Your task is to create more functionality to the class by overloading the
``/``, ``<``, ``>``, ``==`` and ``!=`` operators. ``GeomVector`` objects are equal if all
their components are equal (``x``, ``y`` and ``z``). ``<`` and ``>`` should compare
the vector by length (use the ``Length`` function).

To access the GeomVector itself, you can use ``this``, which is a pointer
to the object itself. So, to get the length of the vector being compared
to another, you'd do ``this->Length()``.
