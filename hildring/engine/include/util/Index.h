#pragma once

namespace util {

template <typename DataType = int, DataType InvalidValue = -1>
class Index {
public:
    Index(DataType _value = InvalidValue)
        : value(_value)
    {
    }

    bool valid() { return value != InvalidValue; }

    Index& operator=(DataType _value)
    {
        value = _value;
        return *this;
    }

    operator DataType() const
    {
        return value;
    }

    void invalidate()
    {
        value = InvalidValue;
    }

private:
    DataType value;
};
}
