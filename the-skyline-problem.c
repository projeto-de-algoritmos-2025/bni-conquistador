#include <stdlib.h>
#include <string.h>

#define MAX(A,B) (((A)>(B)) ? (A) : (B))

int** merge(int** left, int sizel, int* coll, int** right, int sizer, int* colr, int* retsize, int** retcol){
    int cap = sizel + sizer, **res = malloc(sizeof(int*) * cap);
    *retcol = malloc(sizeof(int) * cap);
    int l = 0, r = 0, idx = 0, h1 = 0, h2 = 0, lastH = -1;
    while (l < sizel && r < sizer) {
        int x, maxh;
        if (left[l][0] < right[r][0])
            x = left[l][0], h1 = left[l][1],
            maxh = MAX(h1, h2),
            l++;
        else if (left[l][0] > right[r][0])
            x = right[r][0], h2 = right[r][1],
            maxh = MAX(h1, h2),
            r++;
        else
            x = left[l][0], h1 = left[l][1], h2 = right[r][1],
            maxh = MAX(h1, h2),
            l++, r++;

        if (idx == 0 || maxh != lastH)
            res[idx] = malloc(2 * sizeof(int)),
            res[idx][0] = x, res[idx][1] = maxh,
            (*retcol)[idx] = 2,
            lastH = maxh,
            idx++;
    }
    while (l < sizel) {
        int x = left[l][0], h = left[l][1];
        if (idx == 0 || h != lastH)
            res[idx] = malloc(2 * sizeof(int)),
            res[idx][0] = x, res[idx][1] = h,
            (*retcol)[idx] = 2,
            lastH = h,
            idx++;
        l++;
    }
    while (r < sizer) {
        int x = right[r][0], h = right[r][1];
        if (idx == 0 || h != lastH)
            res[idx] = malloc(2 * sizeof(int)),
            res[idx][0] = x, res[idx][1] = h,
            (*retcol)[idx] = 2,
            lastH = h,
            idx++;
        r++;
    }
    *retsize = idx;
    return res;
}

int** skylineDC(int **buildings, int left, int right, int *retsize, int **retcol) {
    if (left > right) {
        *retsize = 0, *retcol = NULL;
        return NULL;
    }
    if (left == right) {
        int L = buildings[left][0], R = buildings[left][1], H = buildings[left][2],
				**res = malloc(sizeof(int*) * 2);
        *retcol = malloc(sizeof(int) * 2);
        res[0] = malloc(2 * sizeof(int)), res[0][0]= L, res[0][1]= H, (*retcol)[0] = 2;
        res[1] = malloc(2 * sizeof(int)), res[1][0]= R, res[1][1]= 0, (*retcol)[1] = 2;
        *retsize = 2;
        return res;
    }
    int mid = (left + right) / 2, *coll, sizel, *colr, sizer,
		**leftsky = skylineDC(buildings, left, mid, &sizel, &coll),
		** rightsky = skylineDC(buildings, mid + 1, right, &sizer, &colr);

    int *mergedcol, mergedsize,
		**merged = merge(leftsky, sizel, coll, rightsky, sizer, colr, &mergedsize, &mergedcol);

    for(int i = 0; i < sizel; i++) free(leftsky[i]);
    for(int i = 0; i < sizer; i++) free(rightsky[i]);
    free(leftsky), free(rightsky), free(coll), free(colr);
    *retsize = mergedsize, *retcol = mergedcol;
    return merged;
}

int** getSkyline(int** buildings, int buildingsSize, int* buildingsColSize,
                 int* returnSize, int** returnColumnSizes) {
    if (buildingsSize == 0) {
        *returnSize = 0, *returnColumnSizes = NULL;
        return NULL;
    }
    return skylineDC(buildings, 0, buildingsSize-1, returnSize, returnColumnSizes);
}
