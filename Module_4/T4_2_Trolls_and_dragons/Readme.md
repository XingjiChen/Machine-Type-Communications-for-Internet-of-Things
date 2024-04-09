**Objective:** Learning to prepare class to support stream output
by overloading the ``<<`` operator.

The templates include slightly modified implementations of the **Troll** 
and **Dragon** classes that were shown in the material.
Enhance the classes so that they support the '<<' operator for output streams,
and the main function following the class definitions compiles.

When Troll name is "Erkki" and hitpoints are 5, the output format should be:

``Troll Erkki with 5 HP``

When Dragon name is "Mirja" and hitpoints are 35, the output format should be:

``Dragon Mirja with 35 HP``

When the exercise works properly, it should output

``Trolls are: Troll Diiba with 10 HP and Troll Urkki with 15 HP``
``Dragons are: Dragon Rhaegal with 50 HP and Dragon Viserion with 55 HP``
