#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>

#include "serializer.h"

class Serializable {
protected:
    Serializable() = default;

public:
    virtual std::string serialize(Serializer& szr) const = 0;

    Serializable(const Serializable&) = delete;
    Serializable& operator=(const Serializable&) = delete;

    Serializable(Serializable&&) = default;
    Serializable& operator=(Serializable&&) = default;

    virtual ~Serializable() = default;
};

#endif
