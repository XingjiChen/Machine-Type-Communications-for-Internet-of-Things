#ifndef AALTO_ELEC_CPP_DUCK_CLASS
#define AALTO_ELEC_CPP_DUCK_CLASS

#include "bird.hpp"

/**
 * \brief TODO: Implement the Duck class.
 *
 * Class' constructor takes a string as a parameter, which is the duck's name.
 * When the Speak method is called a duck should say: <name>: QUACK\n
 * into the stream given as the argument.
 *
 * Due to the simplicity of the class, all of its member functions are
 * implemented in this header file.
 */
class Duck : public Bird {
public:
    explicit Duck(const std::string& name) : Bird(name) {}

    virtual void Speak(std::ostream& os) const override {
        os << GetName() << ": QUACK\n";
    }
};


#endif