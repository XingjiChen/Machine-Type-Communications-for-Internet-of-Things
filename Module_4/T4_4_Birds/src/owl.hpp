#ifndef AALTO_ELEC_CPP_OWL_CLASS
#define AALTO_ELEC_CPP_OWL_CLASS

#include "bird.hpp"

/**
 * \brief TODO: Implement the Owl class.
 *
 * Class' constructor takes a string as an argument, which is the owl's name.
 * When the Speak method is called an owl should say: <name>: WHUU\n
 * into the stream given as the argument.
 *
 * Due to the simplicity of the class, all of its member functions are
 * implemented in this header file.
 */
class Owl : public Bird {
public:
    explicit Owl(const std::string& name) : Bird(name) {}

    virtual void Speak(std::ostream& os) const override {
        os << GetName() << ": WHUU\n";
    }
};


#endif