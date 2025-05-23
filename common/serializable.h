#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <string>

class Serializer;

class Serializable {
protected:
    Serializable() = default;

public:
    virtual std::string serialize() const = 0;

    Serializable(const Serializable&) = delete;
    Serializable& operator=(const Serializable&) = delete;

    Serializable(Serializable&&) = default;
    Serializable& operator=(Serializable&&) = default;

    virtual ~Serializable() = default;
};

#endif
