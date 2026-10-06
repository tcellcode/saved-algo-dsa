void addRegion(int a, int A, int b, int B, int val)
{
    diff[a][b]         += val;
    diff[a][B + 1]     -= val;
    diff[A + 1][b]     -= val;
    diff[A + 1][B + 1] += val;
}
