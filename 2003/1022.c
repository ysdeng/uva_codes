#include <stdio.h>
#include <stdlib.h>

int holePointCount, coverPointCount;
typedef struct {
	int x, y;
} Point;

Point holep[55], coverp[55];

typedef struct {
	int x1, y1, x2, y2;
	int type;
	/*
		1: vertical	y2 > y1
		2: vertical	y2 < y1
		3: horizon	x2 < x1
		4: horizon	x2 > x1
	*/
} Edge;

Edge holeEdge[55], coverEdge[55], tmpEdge[55];

typedef struct {
	int hv, cv, hh, ch;
} MatchIndex;

MatchIndex match[26*26*26*26];
int matchCount;

int x_offset, y_offset;

typedef struct {
	int x, y;
	int hORc;
	/*
		0: hole
		1: cover
	*/
} PointWithType;

void computeEdges();
void findMatchEdges();
int matchLegalChecking(int cur);
	int isOverlaped(int h1, int h2, int c1, int c2);
void moveHoleEdges(int x, int y);
int slicingAlgorithm();
	int cmpSX(const void *a, const void *b);
int plainSweeping(int x);
	int isInside(int n, int a, int b);
	int cmpFY(const void *a, const void *b);

int main () {
	int testcase = 0;
	int i, j, k, l;
	int cur;
	int islegal, isCovered;

	while(1) {
		scanf("%d%d", &holePointCount, &coverPointCount);
		if(holePointCount == 0 && coverPointCount == 0) break;

		for(i = 1; i <= holePointCount; i++)
			scanf("%d%d", &holep[i].x, &holep[i].y);
		for(i = 1; i <= coverPointCount; i++)
			scanf("%d%d", &coverp[i].x, &coverp[i].y);

		computeEdges();

		findMatchEdges();

		cur = 0;
		isCovered = 0;
		while(1) {
			cur++;
			if(cur == matchCount) break;

			islegal = matchLegalChecking(cur);
			if(islegal == 0) continue;

			moveHoleEdges(x_offset, y_offset);
			isCovered = slicingAlgorithm();
			if(isCovered == 1)
				break;	
		}

		/* output */
		printf("Hole %d: ", ++testcase);
		if(isCovered) puts("Yes");
		else puts("No");

	}
	return 0;
}

void computeEdges () {
	int i;
	for(i = 1; i <= holePointCount; i++) {
		holeEdge[i].x1 = holep[i].x, holeEdge[i].y1 = holep[i].y;
		if(i == holePointCount)
			holeEdge[i].x2 = holep[1].x, holeEdge[i].y2 = holep[1].y;
		else
			holeEdge[i].x2 = holep[i+1].x, holeEdge[i].y2 = holep[i+1].y;

		if(holeEdge[i].x1 == holeEdge[i].x2)
			holeEdge[i].type = (holeEdge[i].y2 > holeEdge[i].y1)? 1: 2;
		else
			holeEdge[i].type = (holeEdge[i].x2 > holeEdge[i].x1)? 4: 3;
	}
	for(i = 1; i <= coverPointCount; i++) {
		coverEdge[i].x1 = coverp[i].x, coverEdge[i].y1 = coverp[i].y;
		if(i == coverPointCount)
			coverEdge[i].x2 = coverp[1].x, coverEdge[i].y2 = coverp[1].y;
		else
			coverEdge[i].x2 = coverp[i+1].x, coverEdge[i].y2 = coverp[i+1].y;

		if(coverEdge[i].x1 == coverEdge[i].x2)
			coverEdge[i].type = (coverEdge[i].y2 > coverEdge[i].y1)? 1: 2;
		else
			coverEdge[i].type = (coverEdge[i].x2 > coverEdge[i].x1)? 4: 3;
	}
}

void findMatchEdges () {
	int i, j, k, l;
	int pointer = 1;

	for(i = 1; i <= holePointCount; i++) {
		if(holeEdge[i].type > 2)
			continue;
		for(j = 1; j <= coverPointCount; j++) {
			if(coverEdge[j].type > 2)
				continue;
			if(coverEdge[j].type != holeEdge[i].type)
				continue;
			for(k = 1; k <= holePointCount; k++) {
				if(holeEdge[k].type < 3)
					continue;
				for(l = 1; l <= coverPointCount; l++) {
					if(coverEdge[l].type < 3)
						continue;
					if(coverEdge[l].type != holeEdge[k].type)
						continue;
					match[pointer].hv = i;
					match[pointer].cv = j;
					match[pointer].hh = k;
					match[pointer].ch = l;
					pointer++;
				}
			}
		}
	}

	matchCount = pointer;
}

int matchLegalChecking (int cur) {
	int hv, cv, hh, ch;
	hv = match[cur].hv;
	cv = match[cur].cv;
	hh = match[cur].hh;
	ch = match[cur].ch;

	x_offset = coverEdge[cv].x1 - holeEdge[hv].x1;
	y_offset = coverEdge[ch].y1 - holeEdge[hh].y1;

	if(isOverlaped(holeEdge[hh].x1 + x_offset, holeEdge[hh].x2 + x_offset, coverEdge[ch].x1, coverEdge[ch].x2) == 1
	&& isOverlaped(holeEdge[hv].y1 + y_offset, holeEdge[hv].y2 + y_offset, coverEdge[cv].y1, coverEdge[cv].y2) == 1)
		return 1;

	return 0;
}

int isOverlaped (int h1, int h2, int c1, int c2) {
	int hMin = (h1 > h2)? h2 : h1; 
	int hMax = (h1 > h2)? h1 : h2;
	int cMin = (c1 > c2)? c2 : c1;
	int cMax = (c1 > c2)? c1 : c2;

	if(cMin >= hMax || hMin >= cMax) return 0;
	else return 1;
}

void moveHoleEdges (int x, int y) {
	int i;

	for(i = 1; i <= holePointCount; i++) {
		tmpEdge[i].x1 = holeEdge[i].x1 + x_offset;
		tmpEdge[i].y1 = holeEdge[i].y1 + y_offset;
		tmpEdge[i].x2 = holeEdge[i].x2 + x_offset;
		tmpEdge[i].y2 = holeEdge[i].y2 + y_offset;
		tmpEdge[i].type = holeEdge[i].type;
	}
}

int cmpSX (const void *a, const void *b) {
	PointWithType *c = (PointWithType *)a;
	PointWithType *d = (PointWithType *)b;

	return (c->x - d->x);
}

int slicingAlgorithm () {
	int i, j, k;
	PointWithType slicePoint[150];
	int slicePointCount = 0;
	int flag;

	/* find slicing points X */
	for(i = 1; i <= holePointCount; i++) {
		if(tmpEdge[i].type < 3)
			continue;
		slicePoint[slicePointCount].x = tmpEdge[i].x1;
		slicePoint[slicePointCount].hORc = 0;
		slicePointCount++;
	}
	for(i = 1; i <= coverPointCount; i++) {
		if(coverEdge[i].type < 3)
			continue;
		slicePoint[slicePointCount].x = coverEdge[i].x1;
		slicePoint[slicePointCount].hORc = 1;
		slicePointCount++;
	}

	/* sort slicing point X */
	qsort(slicePoint, slicePointCount, sizeof(slicePoint[0]), cmpSX);

	/*
		if hole's leftest edge < cover's leftest edge,
		than must can't cover
	*/
	if((slicePoint[0].x != slicePoint[1].x)
		&& (slicePoint[0].hORc == 0))
		return 0; 
	if((slicePoint[slicePointCount-1].x != slicePoint[slicePointCount-2].x)
		&& (slicePoint[slicePointCount-1].hORc == 0))
		return 0;

	/*
		before do sliceing,
		only need to slice the part that hole contained
	*/
	int mini = 150, maxi = 0;
	for(i = 0; i < slicePointCount; i++) {
		if(slicePoint[i].hORc == 0) {
			if(i < mini) mini = i;
			if(i > maxi) maxi = i;
		}
	}

	/* do slicing and plain sweeping */
	for(i = mini; i < maxi; i++) {
		/* the last slicing point needn't check */
		if(i > 0 && slicePoint[i].x == slicePoint[i-1].x)
			continue;
		flag = plainSweeping(slicePoint[i].x);
		if(flag == 1) return 0;
	}

	if(flag == 0) return 1;
	else return 0;
}

int isInside (int n, int a, int b) {
	int Min = (a > b)? b: a;
	int Max = (a > b)? a: b;

	if(n < Min || n >= Max) return 0;
	else return 1;
}

int cmpFY (const void *a, const void *b) {
	PointWithType *c = (PointWithType *)a;
	PointWithType *d = (PointWithType *)b;

	if(c->y != d->y) return (c->y - d->y);
	else return (c->hORc - d->hORc);
}

int plainSweeping (int x) {
	/* if fail return 1 */
	int i, j, k;
	PointWithType fragment[150];
	int fragmentCount = 0;

	/* find sweeping points Y */
	for(i = 1; i <= holePointCount; i++) {
		if(tmpEdge[i].type > 2) {
			if(1 == isInside(x, tmpEdge[i].x1, tmpEdge[i].x2)) {
				fragment[fragmentCount].y = tmpEdge[i].y1;
				fragment[fragmentCount].hORc = 0;
				fragmentCount++;
			}
		}
	}

	for(i = 1; i <= coverPointCount; i++) {
		if(coverEdge[i].type > 2) {
			if(1 == isInside(x, coverEdge[i].x1, coverEdge[i].x2)) {
				fragment[fragmentCount].y = coverEdge[i].y1;
				fragment[fragmentCount].hORc = 1;
				fragmentCount++;
			}
		}
	}

	/* sort sweeping points Y */
	qsort(fragment, fragmentCount, sizeof(fragment[0]), cmpFY);

	/* sort for the same Y */
	int hInOut = 0; /* 0: In 1: Out */
	int cInOut = 0;
	for(i = 0; i < fragmentCount; i++) {
		if(fragment[i].hORc == 1) {
			fragment[i].x = hInOut;
			hInOut = (hInOut)? 0: 1;
		}
		else {
			fragment[i].x = cInOut;
			cInOut = (cInOut)? 0: 1;
		}
	}

	PointWithType temp;
	for(i = 1; i < fragmentCount; i++) {
		if(fragment[i].y == fragment[i-1].y) {
			if(fragment[i-1].x == 1) ;
			else {
				temp = fragment[i];
				fragment[i] = fragment[i-1];
				fragment[i-1] = temp;
			}
		}
	}

	/* start sweeping */
	int flagH = 0;
	int flagC = 0;
	int FLAG = 0;
	for(i = 0; i < fragmentCount; i++) {
		if(fragment[i].hORc == 1) {
			if(flagC == 0) {
				if(flagH == 1) FLAG = 1;
				else flagC = 1;
			}
			else {
				if(flagH == 1) FLAG = 1;
				else flagC = 0;
			}
		}
		else {
			if(flagH == 0) {
				if(flagC == 0) FLAG = 1;
				else flagH = 1;
			}
			else {
				if(flagC == 0) FLAG = 1;
				else flagH = 0;
			}
		}
		if(FLAG) break;
	}

	if(FLAG) return 1;
	else return 0;
}
