#pragma once

#include "table.h"
#include "polynomial.h"
#include <gtest.h>

// === UNORDERED TABLE ===

TEST(unordered_table, can_create_unordered_table)
{
	ASSERT_NO_THROW(unordered_table<polynomial> t);

	unordered_table<polynomial> t;
	t.insert(3, polynomial("-30.2+xyz"));
	t.insert(0, polynomial("7x^9-3yz^2"));
	t.insert(1, polynomial("-5.5xy-z"));
	ASSERT_NO_THROW(unordered_table<polynomial> t1(t));
}

TEST(unordered_table, can_insert) 
{
	unordered_table<polynomial> t0, t1;
	t0.insert(3, polynomial("-30.2+xyz"));
	t0.insert(0, polynomial("7x^9-3yz^2"));
	t0.insert(1, polynomial("-5.5xy-z"));

	t1.insert(3, polynomial("-30.2+xyz"));
	t1.insert(0, polynomial("7x^9-3yz^2"));
	t1.insert(1, polynomial("-5.5xy-z"));
	ASSERT_NO_THROW(t1.insert(1, polynomial("-5.5xy-z")));

	EXPECT_EQ(*t1.find(3), *t0.find(3));
	EXPECT_EQ(*t1.find(0), *t0.find(0));
	EXPECT_EQ(*t1.find(1), *t0.find(1));

	EXPECT_EQ(t0.insert(1, polynomial("3x^2+x+1")), false);
	EXPECT_EQ(t1.insert(1, polynomial("3x^2+x+1")), false);
}

TEST(unordered_table, can_find) 
{
	unordered_table<polynomial> t0;
	t0.insert(3, polynomial("-0.2+x^3yz-5y"));
	t0.insert(0, polynomial("x^4z-2yz^2+4"));
	t0.insert(1, polynomial("-0.5y-z+x"));

	ASSERT_NO_THROW(t0.find(0));
	EXPECT_EQ(*t0.find(0), polynomial("x^4z-2yz^2+4"));
	EXPECT_EQ(t0.find(2), nullptr);
}

TEST(unordered_table, can_erase)
{
	unordered_table<polynomial> t0;
	t0.insert(3, polynomial("-30.2+xyz"));
	t0.insert(0, polynomial("7x^9-3yz^2"));
	t0.insert(1, polynomial("-5.5xy-z"));

	ASSERT_NO_THROW(t0.erase(3));
	EXPECT_EQ(t0.find(3), nullptr);

	t0.erase(1);
	t0.erase(0);
	EXPECT_EQ(t0.erase(1), false);
}

TEST(unordered_table, can_get_size_and_empty) 
{
	unordered_table<polynomial> t;
	EXPECT_EQ(t.empty(), true);

	t.insert(2, polynomial("7.81z+3yx-0.2"));
	EXPECT_EQ(t.empty(), false);

	t.erase(2);
	EXPECT_EQ(t.empty(), true);
}

// === ORDERED TABLE ===

TEST(ordered_table, can_create_ordered_table) 
{
	ASSERT_NO_THROW(ordered_table<polynomial> t);

	ordered_table<polynomial> t;
	t.insert(3, polynomial("yz+xy+zx^7"));
	t.insert(0, polynomial("3x^4+2.2x^2y^3"));
	t.insert(1, polynomial("-2.43xy+7z"));

	ASSERT_NO_THROW(ordered_table<polynomial> t1(t));

}

TEST(ordered_table, can_insert) 
{
	ordered_table<polynomial> t0, t1;
	t0.insert(0, polynomial("7x^9-3yz^2"));
	t0.insert(1, polynomial("-5.5xy-z"));
	t0.insert(3, polynomial("-30.2+xyz"));

	t1.insert(3, polynomial("-30.2+xyz"));
	t1.insert(0, polynomial("7x^9-3yz^2"));
	t1.insert(1, polynomial("-5.5xy-z"));

	EXPECT_EQ(*t1.find(0), *t0.find(0));
	EXPECT_EQ(*t1.find(1), *t0.find(1));
	EXPECT_EQ(*t1.find(3), *t0.find(3));

	EXPECT_EQ(t0.insert(1, polynomial("3x^2+x+1")), false);
}

TEST(ordered_table, can_find) 
{
	ordered_table<polynomial> t0;
	t0.insert(10, polynomial("-0.2+x^3yz-5y"));
	t0.insert(38, polynomial("x^4z-2yz^2+4"));
	t0.insert(0, polynomial("-0.5y-z+x"));

	ASSERT_NO_THROW(t0.find(38));
	EXPECT_EQ(*t0.find(38), polynomial("x^4z-2yz^2+4"));
	EXPECT_EQ(*t0.find(0), polynomial("-0.5y-z+x"));
	EXPECT_EQ(t0.find(9), nullptr);
}

TEST(ordered_table, can_erase) 
{
	ordered_table<polynomial> t0;
	t0.insert(19, polynomial("x^7y-1"));
	t0.insert(17, polynomial("15y+y^3-x^2"));
	t0.insert(18, polynomial("7xy^2-3y^3z^2"));
	t0.insert(1, polynomial("-57.5xy+2zx^3"));

	ASSERT_NO_THROW(t0.erase(19));
	EXPECT_EQ(t0.find(19), nullptr);

	t0.erase(1);
	EXPECT_EQ(t0.find(1), nullptr);

	t0.erase(18);
	t0.erase(17);
	EXPECT_EQ(t0.erase(1), false);
}

// === HASH TABLE ===

TEST(hash_table, can_create_hash_table) 
{
	ASSERT_NO_THROW(hash_table<polynomial> t);

	hash_table<polynomial> t;
	t.insert(3, polynomial("xy+x^7"));
	t.insert(0, polynomial("3x^4+2.2x^2y^3"));
	t.insert(1, polynomial("-2.43xy+7z"));

	ASSERT_NO_THROW(hash_table<polynomial> t1(t));
}

TEST(hash_table, can_find) 
{
	hash_table<polynomial> t0;
	t0.insert(10, polynomial("-0.2z-5y"));
	t0.insert(38, polynomial("z^2+4"));
	t0.insert(0, polynomial("-x"));

	ASSERT_NO_THROW(t0.find(38));
	EXPECT_EQ(*t0.find(38), polynomial("z^2+4"));
	EXPECT_EQ(*t0.find(0), polynomial("-x"));
	EXPECT_EQ(t0.find(9), nullptr);
}

TEST(hash_table, can_insert) 
{
	hash_table<polynomial> t0, t1;
	t0.insert(0, polynomial("15x^2-3yz^2"));
	t0.insert(1, polynomial("-5.5xy-z"));
	t0.insert(3, polynomial("-3xyz"));

	ASSERT_NO_THROW(t1.insert(3, polynomial("-3xyz")));
	t1.insert(0, polynomial("15x^2-3yz^2"));
	t1.insert(1, polynomial("-5.5xy-z"));

	EXPECT_NE(t1.find(0), nullptr);
	EXPECT_NE(t1.find(1), nullptr);
	EXPECT_NE(t1.find(3), nullptr);
	EXPECT_EQ(t1.find(10), nullptr);

	EXPECT_EQ(t0.insert(1, polynomial("3x^2+x+1")), false);
}

TEST(hash_table, can_erase) 
{
	hash_table<polynomial> t0;
	t0.insert(19, polynomial("x^7y-1"));
	t0.insert(17, polynomial("15y+y^3-x^2"));
	t0.insert(18, polynomial("7xy^2-3y^3z^2"));
	t0.insert(1, polynomial("-57.5xy+2zx^3"));

	ASSERT_NO_THROW(t0.erase(19));
	EXPECT_EQ(t0.find(19), nullptr);

	t0.erase(1);
	EXPECT_EQ(t0.find(1), nullptr);

	t0.erase(18);
	t0.erase(17);
	EXPECT_EQ(t0.find(18), nullptr);
	EXPECT_EQ(t0.find(17), nullptr);

	EXPECT_EQ(t0.erase(1), false);
}
