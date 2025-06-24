#pragma once

#include "Sequence.hpp"
#include "LinkedList.hpp"
#include "error.hpp"
#include <stdexcept>

template <typename T>
class MutableListSequence : public Sequence<T> {
private:
    int size;
protected:
    LinkedList<T>* list;

    Sequence<T>* CreateFromList(LinkedList<T>* list) const;

public:
    MutableListSequence();
    MutableListSequence(T* items, int count);
    MutableListSequence(const MutableListSequence<T>& other);
    MutableListSequence(const LinkedList<T>& list);
    ~MutableListSequence() override;

    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    int GetLength() const override;
    T* GetRef(int index) const;

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    Sequence<T>* Concat(const Sequence<T>* other) const override;

    Sequence<T>* Append(T item) override;
    Sequence<T>* Prepend(T item) override;
    Sequence<T>* InsertAt(T item, int index) override;
    Sequence<T>* Remove(int index) override;

    Sequence<T>* Instance() override;
    Sequence<T>* Clone() const override;
};


template <typename T>
MutableListSequence<T>::MutableListSequence() {
    list = new LinkedList<T>();
    size = 0;
}

template <typename T>
MutableListSequence<T>::MutableListSequence(T* items, int count) {
    list = new LinkedList<T>(items, count);
    size = count;
}

template <typename T>
MutableListSequence<T>::MutableListSequence(const MutableListSequence<T>& other) {
    list = new LinkedList<T>(*other.list);
    size = other.size;
}

template <typename T>
MutableListSequence<T>::MutableListSequence(const LinkedList<T>& list) {
    this->list = new LinkedList<T>(list);
    size = list.GetLength();
}

template <typename T>
MutableListSequence<T>::~MutableListSequence() {
    delete list;
}

template <typename T>
T MutableListSequence<T>::GetFirst() const {
    return list->GetFirst();
}

template <typename T>
T MutableListSequence<T>::GetLast() const {
    int i = 0;
    for (; i < size - 1; i++) {}
    return list->Get(i);
}

template <typename T>
T MutableListSequence<T>::Get(int index) const {
    return list->Get(index);
}

template <typename T>
int MutableListSequence<T>::GetLength() const {
    return list->GetLength();
}

template <typename T>
Sequence<T>* MutableListSequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    LinkedList<T>* sub = list->GetSubList(startIndex, endIndex);
    auto* result = new MutableListSequence<T>(*sub);
    delete sub;
    return result;
}

template <typename T>
T* MutableListSequence<T>::GetRef(int index) const {
    return list->GetRef(index);
}

template <typename T>
Sequence<T>* MutableListSequence<T>::Concat(const Sequence<T>* other) const {
    auto otherList = dynamic_cast<const MutableListSequence<T>*>(other);
    if (!otherList) throw Errors::IncompatibleTypes();
    LinkedList<T>* result = list->Concat(otherList->list);
    return CreateFromList(result);
}

template <typename T>
Sequence<T>* MutableListSequence<T>::Append(T item) {
    list->Append(item);
    size++;
    return this;
}

template <typename T>
Sequence<T>* MutableListSequence<T>::Prepend(T item) {
    list->Prepend(item);
    size++;
    return this;
}

template <typename T>
Sequence<T>* MutableListSequence<T>::InsertAt(T item, int index) {
    list->InsertAt(item, index);
    return this;
}

template <typename T>
Sequence<T>* MutableListSequence<T>::Remove(int index) {
    if (list->GetLength() == 0) throw Errors::EmptyList();
    list->Remove(index);
    size--;
    return this;
}

template <typename T>
Sequence<T>* MutableListSequence<T>::Instance() {
    return this;
}

template <typename T>
Sequence<T>* MutableListSequence<T>::Clone() const {
    return new MutableListSequence<T>(*this);
}

template <typename T>
Sequence<T>* MutableListSequence<T>::CreateFromList(LinkedList<T>* list) const {
    return new MutableListSequence<T>(*list);
}

template <typename T>
MutableListSequence<T> operator+(const MutableListSequence<T>& lhs, const MutableListSequence<T>& rhs) {
    Sequence<T>* resultBase = lhs.Concat(&rhs);
    auto* result = static_cast<MutableListSequence<T>*>(resultBase);
    MutableListSequence<T> copy(*result);
    delete result;
    return copy;
}


template <typename T>
class ImmutableListSequence : public MutableListSequence<T> {
public:
    using MutableListSequence<T>::MutableListSequence;

    Sequence<T>* Append(T item) override;
    Sequence<T>* Prepend(T item) override;
    Sequence<T>* InsertAt(T item, int index) override;
    Sequence<T>* Remove(int index) override;

    Sequence<T>* Instance() override;
    Sequence<T>* Clone() const override;
};


template <typename T>
Sequence<T>* ImmutableListSequence<T>::Append(T item) {
    return this->Clone()->Append(item);
}

template <typename T>
Sequence<T>* ImmutableListSequence<T>::Prepend(T item) {
    return this->Clone()->Prepend(item);
}

template <typename T>
Sequence<T>* ImmutableListSequence<T>::InsertAt(T item, int index) {
    return this->Clone()->InsertAt(item, index);
}

template <typename T>
Sequence<T>* ImmutableListSequence<T>::Remove(int index) {
    return this->Clone()->Remove(index);
}

template <typename T>
Sequence<T>* ImmutableListSequence<T>::Instance() {
    return this->Clone();
}

template <typename T>
Sequence<T>* ImmutableListSequence<T>::Clone() const {
    return new ImmutableListSequence<T>(*this);
}

template <typename T>
ImmutableListSequence<T> operator+(const ImmutableListSequence<T>& lhs, const ImmutableListSequence<T>& rhs) {
    Sequence<T>* resultBase = lhs.Concat(&rhs);
    auto* result = static_cast<ImmutableListSequence<T>*>(resultBase);
    ImmutableListSequence<T> copy(*result);
    delete result;
    return copy;
}