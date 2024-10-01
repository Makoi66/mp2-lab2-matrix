#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);

	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(m);
	ASSERT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(m);

	m1[0][0] = 10;

	ASSERT_NE(m[0][0], m1[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	/*TDynamicVector<TDynamicVector<int>> m(5);

	ASSERT_EQ(m.size(), 5);*/

	TDynamicMatrix<int> m(5);

	ASSERT_EQ(m.get_size(), 5);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(5);
	m[0][1] = 4;

	EXPECT_EQ(4, m[0][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(4);

	ASSERT_ANY_THROW(m.at(-1, -1));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(4);

	ASSERT_ANY_THROW(m.at(999, 999));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(3);
	TDynamicMatrix<int> m1(3);
	m[2][1] = 4;
	m1 = m;

	ASSERT_NO_THROW(m = m);
	m = m;

	ASSERT_EQ(m, m1);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(5);
	m[2][1] = 4;

	ASSERT_NO_THROW(m = m1);
	m1 = m;

	ASSERT_EQ(m, m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(2);

	m1 = m;

	EXPECT_EQ(m.get_size(), m1.get_size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(2);
	m[2][1] = 4;

	ASSERT_NO_THROW(m = m1);
	m1 = m;

	ASSERT_EQ(m, m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicVector<int> m(5);
	TDynamicVector<int> m1(5);

	ASSERT_EQ(m == m1, 1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(5);

	ASSERT_EQ(m == m, 1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(5);

	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(2);

	m2[0][0] = 3;
	m2[1][0] = 3;

	m[0][0] = 1;
	m[1][0] = 1;
	m1[0][0] = 2;
	m1[1][0] = 2;

	ASSERT_NO_THROW(m + m1);
	m = m + m1;

	EXPECT_EQ(m, m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(3);

	m[0][0] = 1;
	m[1][0] = 1;
	m1[0][0] = 2;
	m1[1][0] = 2;

	ASSERT_ANY_THROW(m + m1);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(2);

	m[0][0] = 1;
	m[1][0] = 1;
	m1[0][0] = 2;
	m1[1][0] = 2;

	ASSERT_NO_THROW(m - m1);
	m2 = m1 - m;

	EXPECT_EQ(m, m2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m(2);
	TDynamicMatrix<int> m1(3);

	m[0][0] = 1;
	m[1][0] = 1;
	m1[0][0] = 2;
	m1[1][0] = 2;

	ASSERT_ANY_THROW(m - m1);
}

TEST(TDynamicMatrix, can_move_matrix)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(5);
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j) {
			m[i][j] = i * 5 + j;
			m1[i][j] = i * 5 + j;
		}

	TDynamicMatrix<int> m2(std::move(m1));

	ASSERT_EQ(m1.get_size(), 0);
	ASSERT_EQ(m2.get_size(), 5);

	ASSERT_EQ(m, m2);
}

TEST(TDynamicMatrix, can_move_assign_matrix)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(5);
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j) {
			m[i][j] = i * 5 + j;
			m1[i][j] = i * 5 + j;
		}
	TDynamicMatrix<int> m2(2);
	m2 = std::move(m1);
	
	ASSERT_EQ(m1.get_size(), 0);
	ASSERT_EQ(m2.get_size(), 5);

	ASSERT_EQ(m, m2);
}