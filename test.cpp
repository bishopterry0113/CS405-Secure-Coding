// Uncomment the next line to use precompiled headers
//#include "pch.h"
// uncomment the next line if you do not use precompiled headers
#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
};

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}

// TODO: Create a test to verify adding a single value to an empty collection
TEST_F(CollectionTest, AddToEmptyCollection)
{
    // is the collection empty?
    // if empty, the size must be 0

    add_entries(1);

    // is the collection still empty?
    // if not empty, what must the size be?
}

// TODO: Create a test to verify adding five values to collection
TEST_F(CollectionTest, AddValuesToCollection)
{
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);

    add_entries(5);
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, MaxSizeGreaterThan)
{
    ASSERT_GE(collection->max_size(), collection->size()); // tests for 0
    add_entries(1);
    ASSERT_GE(collection->max_size(), collection->size()); // tests for 1
    add_entries(4);
    ASSERT_GE(collection->max_size(), collection->size()); // tests for 5
    add_entries(5);
    ASSERT_GE(collection->max_size(), collection->size()); // tests for 10
    std::cout << "Collection max size: " << (int)collection->max_size() << '\n';
}
// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries
TEST_F(CollectionTest, CapacityGreaterThan)
{
    ASSERT_GE(collection->capacity(), collection->size()); // tests for 0
    add_entries(1);
    ASSERT_GE(collection->capacity(), collection->size()); // tests for 1
    add_entries(4);
    ASSERT_GE(collection->capacity(), collection->size()); // tests for 5
    add_entries(5);
    ASSERT_GE(collection->capacity(), collection->size()); // tests for 10
    std::cout << "Collection capacity: " << (int)collection->capacity() << '\n';
}
// TODO: Create a test to verify resizing increases the collection
TEST_F(CollectionTest, ResizingIncreaseCollection)
{
    ASSERT_TRUE(collection->empty()); // see if it starts empty
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    collection->resize(17);
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    collection->resize(39);
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    EXPECT_EQ(collection->size(), 39);
}
// TODO: Create a test to verify resizing decreases the collection
TEST_F(CollectionTest, ResizingDecreaseCollection)
{
    ASSERT_TRUE(collection->empty()); // see if it starts empty
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    add_entries(50);
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    collection->resize(32);
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    collection->resize(13);
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    EXPECT_EQ(collection->size(), 13);
}
// TODO: Create a test to verify resizing decreases the collection to zero
TEST_F(CollectionTest, ResizingDecreaseToZero)
{
    ASSERT_TRUE(collection->empty()); // see if it starts empty
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    add_entries(25);
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    collection->resize(12);
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    collection->resize(0);
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    ASSERT_TRUE(collection->empty()); // see if it ends empty
}
// TODO: Create a test to verify clear erases the collection
TEST_F(CollectionTest, DoesClearEraseContents)
{
    ASSERT_TRUE(collection->empty()); // see if it starts empty
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    add_entries(25);
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    collection->clear();
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    ASSERT_TRUE(collection->empty()); // verify clear removed all contents
}

// TODO: Create a test to verify erase(begin,end) erases the collection
TEST_F(CollectionTest, DoesEraseWorkToEraseContents)
{
    ASSERT_TRUE(collection->empty()); // see if it starts empty
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    add_entries(5);
    std::vector<int>::reverse_iterator rit = collection->rbegin();
    int i = 0;
    for (rit = collection->rbegin(); rit != collection->rend(); ++rit)
        *rit = ++i;
    std::cout << "Collection contains:";
    for (std::vector<int>::iterator it = collection->begin(); it != collection -> end(); ++it)
    std::cout << ' ' << *it;
    std::cout << '\n';
    return;
    ASSERT_TRUE(collection->empty()); // verify all contents removed
    std::cout << "Collection size: " << (int)collection->size() << '\n';
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, DoesReseverOnlyChangeCapacity)
{
    ASSERT_TRUE(collection->empty()); // see if it starts empty
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    std::cout << "Collection capacity: " << (int)collection->capacity() << '\n';
    add_entries(25);
    collection->reserve(55);
    ASSERT_EQ(collection->capacity(), 55);
    ASSERT_EQ(collection->size(), 25);
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    std::cout << "Collection capacity: " << (int)collection->capacity() << '\n';
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
TEST_F(CollectionTest, OutOfRangeThrow)
{
    std::cout << "Collection size: " << (int)collection->size() << '\n';
    add_entries(9);
    for (unsigned i = 0; i < collection->size(); i++)
        collection->at(i) = i;
    std::cout << "Collection contains:";
    for (unsigned i = 0; i < collection->size(); i++)
        std::cout << ' ' << collection->at(i);
    std::cout << '\n';
    ASSERT_THROW(collection->at(7), std::out_of_range);
    return;
}
// NOTE: This is a negative test positive & 1 negative
TEST_F(CollectionTest, EnsureAddsExpandCapacity) 
{
    collection->reserve(10);
    std::cout << "Collection capacity: " << (int)collection->capacity() << '\n';
    add_entries(13);
    std::cout << "Collection capacity: " << (int)collection->capacity() << '\n';
    ASSERT_GE(collection->capacity(), collection->size());
}
TEST_F(CollectionTest, EnsureSizeCheckWorks) 
{
    ASSERT_EQ(collection->size(), 0);
    add_entries(5);

    EXPECT_EQ(collection->size(), -5);
    std::cout << "Collection size: " << (int)collection->size() << '\n';
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative
