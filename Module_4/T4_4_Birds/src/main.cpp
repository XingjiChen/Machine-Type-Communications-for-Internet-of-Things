#include <iostream>
#include <string>

#include "aviary.hpp"
#include "bird.hpp"
#include "duck.hpp"
#include "owl.hpp"

void ConstTest(const Aviary &a)
{
    a[1]->Speak(std::cout);
}

int main()
{
    /* The output of the program should be this:
    Esko: QUACK
    Orly: WHUU
    Alfred: QUACK
    Alfred flies!
    Orly: WHUU
     */
    Aviary a;

    a.Add(new Duck("Esko"));
    a.Add(new Owl("Orly"));

    a.Add(new Duck("Alfred"));

    a.SpeakAll(std::cout);

    a[2]->Fly(std::cout);

    ConstTest(a);
}
