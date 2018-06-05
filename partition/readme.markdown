������������� n � ���� ����� ������������� ���������.
�����: ������ �����.

OEIS: [A000041](https://oeis.org/A000041)  of partitions of n (the partition s).

������������� � ���� ����� ������������� ��������� ���� �� �� �����, ��� � ������������� n � ���� ����� n ��������������� ���������.

������:
[MathWorld](http://mathworld.wolfram.com/Partition.html),
[���������](https://en.wikipedia.org/wiki/Partition_(number_theory).


������� `total`: O(n^(3/2)).

������� `generate_all`: O(n * answer).

������� `is_valid`: O(n).

������� `_by_object`: O(n*total(n)).

������� `object_by`: O(n*total(n)).

������� `prev`: O(n)

������� `next`: O(n)