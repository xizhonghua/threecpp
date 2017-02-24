/*
 * Property.h
 *
 *  Created on: Feb 24, 2017
 *      Author: zxi
 */

#ifndef THREE_CORE_PROPERTY_H_
#define THREE_CORE_PROPERTY_H_

#include <functional>

namespace three {

typedef std::function<void()> CallbackFunc;

template<typename T>
class Property {
public:

  Property() :
      data_() {
  }

  Property(const T& data) :
      data_(data) {
  }

  Property(const T& data, CallbackFunc callback) :
      data_(data), callback_(callback) {
  }

  Property(CallbackFunc callback) :
      data_(), callback_(callback) {
  }

  inline Property& set(const T& v, bool force_callback = false) {
    data_ = v;
    if (force_callback)
      callback();
    return *this;
  }

  inline Property& operator=(const T& v) {
    data_ = v;
    callback();
    return *this;
  }

  inline Property& operator+=(const T& v) {
    data_ += v;
    callback();
    return *this;
  }

  inline Property& operator-=(const T& v) {
    data_ -= v;
    callback();
    return *this;
  }

  inline Property& operator*=(const T& v) {
    data_ *= v;
    callback();
    return *this;
  }

  inline Property& operator/=(const T& v) {
    data_ /= v;
    callback();
    return *this;
  }

  operator T() const {
    return data_;
  }

  void setCallbackFunc(CallbackFunc func) {
    this->callback_ = func;
  }

private:

  inline void callback() {
    if (callback_ == nullptr)
      return;
    callback_();
  }

  T data_;
  CallbackFunc callback_;
};

} /* namespace three */

#endif /* THREE_CORE_PROPERTY_H_ */
