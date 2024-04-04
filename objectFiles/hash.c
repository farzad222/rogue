unsigned hash(unsigned a)
{
    a = (a ^ 61) ^ (a >> 16);
    a = a + (a << 3);
    a = a ^ (a >> 4);
    a = a * 0x27d4eb2d;
    a = a ^ (a >> 15);
    return a;
}

int idx(int x, int y)
{
    int k = 13;
	return hash((x + k) * (2 * k + 1) + y + k);
}