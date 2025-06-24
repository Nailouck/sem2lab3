#pragma once

#include <assert.h>
#include <iostream>

#include "DynamicArray.hpp"
#include "LinkedList.hpp"
#include "ArraySequence.hpp"
#include "ListSequence.hpp"

#include "Stack.hpp"
#include "Queue.hpp"
#include "Deque.hpp"

#include "User.hpp"


void DynamicArrayTest() {
    std::cout << "DynamicArray tests: ";
    DynamicArray<int> arr(3);
    arr.Set(0, 10);
    arr.Set(1, 20);
    arr.Set(2, 30);

    DynamicArray<int> expected1(3);
    expected1.Set(0, 10);
    expected1.Set(1, 20);
    expected1.Set(2, 30);
    assert(arr == expected1);

    arr.Resize(5);
    assert(arr.GetSize() == 5);

    arr.Resize(2);
    DynamicArray<int> expected2(2);
    expected2.Set(0, 10);
    expected2.Set(1, 20);
    assert(arr == expected2);

    arr.Remove(1);
    assert(arr.GetSize() == 1);

    std::cout << "all tests were completed successfully.\n";
}

void LinkedListTest() {
    std::cout << "LinkedList tests: ";
    LinkedList<int> list;
    list.Append(1);
    list.Append(2);
    list.Prepend(0);

    assert(list.GetLength() == 3);
    assert(list.GetFirst() == 0);
    assert(list.GetLast() == 2);
    assert(list.Get(1) == 1);


    list.InsertAt(5, 1);
    assert(list.Get(1) == 5);
    assert(list.Get(2) == 1);

    LinkedList<int>* sub = list.GetSubList(1, 2);
    assert(sub->GetLength() == 2);
    assert(sub->Get(0) == 5);
    assert(sub->Get(1) == 1);

    std::cout << "all tests were completed successfully.\n";
}

void ArraySequenceTest() {
    std::cout << "ArraySequence tests: ";
    MutableArraySequence<int> seq;
    seq.Append(1);
    seq.Append(2);
    seq.Prepend(0);

    assert(seq.GetLength() == 3);
    assert(seq.Get(0) == 0);
    assert(seq.Get(2) == 2);

    seq.InsertAt(5, 1);
    assert(seq.Get(1) == 5);
    assert(seq.Get(2) == 1);

    auto sub = seq.GetSubsequence(1, 3);
    assert(sub->GetLength() == 3);
    assert(sub->Get(0) == 5);

    std::cout << "all tests were completed successfully.\n";
}

void ListSequenceTest() {
    std::cout << "ListSequence tests: ";

    MutableListSequence<int> seq;
    seq.Append(1);
    seq.Append(2);
    seq.Prepend(0);

    assert(seq.GetLength() == 3);
    assert(seq.Get(0) == 0);
    assert(seq.Get(2) == 2);

    seq.InsertAt(5, 1);
    assert(seq.Get(1) == 5);
    assert(seq.Get(2) == 1);

    auto sub = seq.GetSubsequence(1, 3);
    assert(sub->GetLength() == 3);
    assert(sub->Get(0) == 5);

    std::cout << "all tests were completed successfully.\n";
}

void ArrayQueueTest() {
    std::cout << "ArrayQueue tests: ";
    ArrayQueue<int> q;
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    assert(q.GetLength() == 3);
    assert(q.Peek() == 1);
    assert(q.Dequeue() == 1);
    assert(q.Get(0) == 2);
    std::cout << "all tests were completed successfully.\n";
}

void ListQueueTest() {
    std::cout << "ListQueue tests: ";
    ListQueue<int> q;
    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);
    assert(q.GetLength() == 3);
    assert(q.Peek() == 10);
    assert(q.Dequeue() == 10);
    assert(q.Get(0) == 20);
    std::cout << "all tests were completed successfully.\n";
}

void ArrayStackTest() {
    std::cout << "ArrayStack tests: ";
    ArrayStack<std::string> st;
    st.Push("hello");
    st.Push("world");
    assert(st.Top() == "world");
    assert(st.Pop() == "world");
    assert(st.Top() == "hello");
    assert(st.GetLength() == 1);
    std::cout << "all tests were completed successfully.\n";
}

void ListStackTest() {
    std::cout << "ListStack tests: ";
    ListStack<int> st;
    st.Push(3);
    st.Push(2);
    assert(st.Top() == 2);
    assert(st.Pop() == 2);
    assert(st.Get(0) == 3);
    std::cout << "all tests were completed successfully.\n";
}

void ArrayDequeTest() {
    std::cout << "ArrayDeque tests: ";
    ArrayDeque<int> d;
    d.PushBack(1);
    d.PushFront(0);
    d.PushBack(2);
    assert(d.Front() == 0);
    assert(d.Back() == 2);
    assert(d.PopFront() == 0);
    assert(d.PopBack() == 2);
    assert(d.GetLength() == 1);
    std::cout << "all tests were completed successfully.\n";
}

void ListDequeTest() {
    std::cout << "ListDeque tests: ";
    ListDeque<char> d;
    d.PushBack('a');
    d.PushFront('z');
    d.PushBack('b');
    assert(d.Front() == 'z');
    assert(d.Back() == 'b');
    d.PopBack();
    assert(d.Back() == 'a');
    std::cout << "all tests were completed successfully.\n";
}

void StudentTest() {
    std::cout << "Student/Professor tests: ";
    Student s1("Bulgur", 20, 101, "A23-564", true);
    Student s2("Alexei", 19, 287, "B24-511", true);
    Student s3("Danila", 17, 543, "S25-801", true);

    ArrayStack<Student> st_st;
    st_st.Push(s1);
    st_st.Push(s2);
    assert(st_st.Top() == s2);
    assert(st_st.Pop() == s2);
    assert(st_st.Top() == s1);


    ArrayDeque<Student> st_d;
    st_d.PushBack(s1);
    st_d.PushFront(s2);
    st_d.PushBack(s3);
    assert(st_d.Front() == s2);
    assert(st_d.Back() == s3);
    assert(st_d.Get(1) == s1);


    ListQueue<Student> st_q;
    st_q.Enqueue(s1);
    st_q.Enqueue(s2);
    assert(st_q.Peek() == s1);
    assert(st_q.Dequeue() == s1);
    assert(st_q.Get(0) == s2);


    


    Student copy = s1;
    assert(copy == s1);
    copy.age = 218;
    assert(!(copy == s1));


    Professor p1("Dmitry Victorovich", 52, 102, "Physic", true);
    Professor p2("Vladimir Vladimirovich", 30, 1, "PATD", true);
    Professor p3("Tatyana Dmitrievna", 42, 143, "History", false);

    ListStack<Professor> pr_st;
    pr_st.Push(p1);
    pr_st.Push(p2);
    assert(pr_st.Top() == p2);
    assert(pr_st.Pop() == p2);
    assert(pr_st.Top() == p1);


    ArrayDeque<Professor> pr_d;
    pr_d.PushBack(p1);
    pr_d.PushFront(p2);
    pr_d.PushBack(p3);
    assert(pr_d.Front() == p2);
    assert(pr_d.Back() == p3);
    assert(pr_d.Get(1) == p1);


    ListQueue<Professor> pr_q;
    pr_q.Enqueue(p1);
    pr_q.Enqueue(p2);
    assert(pr_q.Peek() == p1);
    assert(pr_q.Dequeue() == p1);
    assert(pr_q.Get(0) == p2);


    std::cout << "all tests were completed successfully.\n";
}

void AllTests() {

    DynamicArrayTest();
    LinkedListTest();

    ArraySequenceTest();
    ListSequenceTest();

    ArrayQueueTest();
    ListQueueTest();

    ArrayStackTest();
    ListStackTest();

    ArrayDequeTest();
    ListDequeTest();

    StudentTest();
}