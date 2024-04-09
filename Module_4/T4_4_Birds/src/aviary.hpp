#ifndef AALTO_ELEC_CPP_AVIARY_CLASS
#define AALTO_ELEC_CPP_AVIARY_CLASS

#include <iostream>
#include <vector>
#include <stdexcept>

#include "bird.hpp"

class Aviary {
public:
    Aviary() {}

    // Disallow copying
    Aviary(const Aviary&) = delete;
    Aviary& operator=(const Aviary&) = delete;

    // Add a bird to the aviary
    void Add(Bird* bird) {
        if (bird == nullptr) {
            throw std::logic_error("Null bird cannot be added to the aviary");
        }
        birds_.push_back(bird);
    }

    // Speak all birds in the aviary
    void SpeakAll(std::ostream& os) const {
        for (const auto& bird : birds_) {
            bird->Speak(os);
        }
    }

    // Get the number of birds in the aviary
    size_t Size() const {
        return birds_.size();
    }

    // Non-const indexing operator
    Bird* operator[](size_t idx) {
        if (idx >= birds_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return birds_[idx];
    }

    // Const indexing operator
    const Bird* operator[](size_t idx) const {
        if (idx >= birds_.size()) {
            throw std::out_of_range("Index out of range");
        }
        return birds_[idx];
    }

    // Destructor
    ~Aviary() {
        for (auto bird : birds_) {
            delete bird;
        }
    }

private:
    std::vector<Bird*> birds_;  // Vector to store pointers to birds
};

#endif // AALTO_ELEC_CPP_AVIARY_CLASS
