#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define min(x,y) (((x)>(y))?(y):(x))
#define max(x,y) (((x)<(y))?(y):(x))

typedef struct {
	int x, y;
} Point;
typedef struct {
	int x1, x2;
	int y1, y2;
	int direction;
	/*
		+1	up	, right
		-1	down, left	
	*/
} Line;
typedef struct {
	int x1, x2;
	int y1, y2;
	int direction;
	/*
		+1	up	, right
		-1	down, left	
	*/
	int type;
	/*
		+1	Cover
		-1	Hole
	*/
} LineWithType;
typedef struct {
	Point point[60];	int p_count;
	long long area;
} Polygon;

/* foliowing 4 lines are for contact edges */
Line hole_vline[60];		int hole_v_count;
Line hole_hline[60];		int hole_h_count;
Line cover_vline[60];		int cover_v_count;
Line cover_hline[60];		int cover_h_count;

LineWithType hLine[200];
LineWithType vLine[200];
int hLineCount, vLineCount;

Polygon hole, cover;

void checkCounterClockwise();
/* 
	calculate the area 
	and change the direction to counterclockwise
*/

int func();
int planeSweeping(int offsetx, int offsety);

int cmp_VL(const void *pa,const void *pb) {
	
	LineWithType *a = (LineWithType *)pa;
	LineWithType *b = (LineWithType *)pb;

	int xa, xb;
	xa = a->x1;
	xb = b->x1;
	return (xa < xb) ? -1 : 1;
}
int cmp_HL(const void *pa,const void *pb) {
	LineWithType *a = (LineWithType *)pa;
	LineWithType *b = (LineWithType *)pb;

	int ya, yb;
	ya = a->y1;
	yb = b->y1;

	if(ya > yb) return 1;
	else if(ya < yb) return -1;
	else {
		int typea, typeb, dira, dirb;
		typea = a->type;
		typeb = b->type;
		dira = a->direction;
		dirb = b->direction;
		if(dira == dirb) {
			return (typea > typeb) ? -1: 1;
		}
		else return (dira > dirb) ? 1: -1;
	}
}

int main () {
	int testcase = 0;
	int i, j, k, l;
	while(2 ==scanf("%d%d", &hole.p_count, &cover.p_count)) {
		if(hole.p_count == 0 && cover.p_count == 0) break;

		/* read input */
		for(i = 0; i < hole.p_count; i++)
			scanf("%d%d", &hole.point[i].x, &hole.point[i].y);
		hole.point[hole.p_count] = hole.point[0];
		for(i = 0; i < cover.p_count; i++)
			scanf("%d%d", &cover.point[i].x, &cover.point[i].y);
		cover.point[cover.p_count] = cover.point[0];

		/* both cover and hole convert to CounterClockwise */
		checkCounterClockwise();
		
		/* main function */
		int success = func();
		/* output */
		printf("Hole %d: ", ++testcase);
		if(success) puts("Yes");
		else puts("No");
		
	}
	return 0;
}

int func() {
	int i, j, k, l, m, n;
	int offset_x, offset_y;
	if(cover.area < hole.area) return 0;
	
	for(i = 0; i < hole_v_count; i++) {
		for(j = 0; j < cover_v_count; j++) {
			if(hole_vline[i].direction != cover_vline[j].direction)
				continue;
			offset_x = hole_vline[i].x1 - cover_vline[j].x1;
			
			for(k = 0; k < hole_h_count; k++) {
				for(l = 0; l < cover_h_count; l++) {
					if(hole_hline[k].direction != cover_hline[l].direction)
						continue;
					offset_y = hole_hline[k].y1 - cover_hline[l].y1;

					/* switch cover */
					for(m = 0; m < hLineCount; m++) {
						if(hLine[m].type == 1) {
							hLine[m].x1 -= offset_x; hLine[m].x2 -= offset_x;
							hLine[m].y1 -= offset_y; hLine[m].y2 -= offset_y;
						}
					}
					for(m = 0; m < vLineCount; m++) {
						if(vLine[m].type == 1) {
							vLine[m].x1 -= offset_x; vLine[m].x2 -= offset_x;
							vLine[m].y1 -= offset_y; vLine[m].y2 -= offset_y;
						}
					}

					int ps = planeSweeping(offset_x, offset_y);
					if(ps == 1) return 1;

					/* switch cover */
					for(m = 0; m < hLineCount; m++) {
						if(hLine[m].type == 1) {
							hLine[m].x1 += offset_x; hLine[m].x2 += offset_x;
							hLine[m].y1 += offset_y; hLine[m].y2 += offset_y;
						}
					}
					for(m = 0; m < vLineCount; m++) {
						if(vLine[m].type == 1) {
							vLine[m].x1 += offset_x; vLine[m].x2 += offset_x;
							vLine[m].y1 += offset_y; vLine[m].y2 += offset_y;
						}
					}
				}
			}
		}
	}
	return 0;
}

int planeSweeping(int offsetx, int offsety) {
	int i, j, k;
	int successCovered = 0;
	
	/* sort vertical lines to do slicing */
	qsort(vLine, vLineCount, sizeof(LineWithType),cmp_VL);
	/* sort horizon lines to know the top-down order */
	qsort(hLine, hLineCount, sizeof(LineWithType),cmp_HL);
	
	/* extract all x for slicing boundary*/
	int xx[200], xxCount;
	xxCount = 0;
	xx[0] = vLine[0].x1;
	int hCount;
	hCount = 0;
	for(i = 1, xxCount = 1; i < vLineCount; i++) {
		if(vLine[i].type == -1) {
			hCount++;
			if(hCount == hole_v_count) break;
		}
		if(xx[xxCount-1] != vLine[i].x1 && hCount)
			xx[xxCount++] = vLine[i].x1;
	}
	/* scan hLine per slice*/
	bool coverInt = 0, holeInt = 0;
	/* -1: empty, 1: nonempty */
	successCovered = 1;
	
	/* the boundary is xx[i] to xx[i+1] */
	for(i = 0; i < xxCount-1; i++) {
		for(j = 0; j < hLineCount; j++) {
			if(min( hLine[j].x1, hLine[j].x2) <= xx[i] &&
				max( hLine[j].x1, hLine[j].x2) >= xx[i+1]) {
				if(hLine[j].type == 1) coverInt = !coverInt;
				else holeInt = !holeInt;
			}
			if(coverInt == false && holeInt == true) {
				return 0;
			}
		}
	}
	return successCovered;
}

void checkCounterClockwise() {
	/* hole */
	int i, j;
	long long tmp_xy, tmp_yx;

	hLineCount = vLineCount = 0;

	tmp_xy = 0;
	for(i = 0; i < hole.p_count; i++) {
		tmp_xy += hole.point[i].x * hole.point[i+1].y;
		tmp_xy -= hole.point[i].y * hole.point[i+1].x;
	}
	
	hole.area = tmp_xy;
	if(hole.area < 0) {
		hole.area *= -1;
		/*
		Point tmp_point[60];
		for(i = 0, j = hole.p_count; j >= 0; i++, j--) {
			tmp_point[i] = hole.point[j];
		}
		for(i = 0; i <= hole.p_count; i++) {
			hole.point[i] = tmp_point[i];
		}
		*/
	}

	hole_v_count = hole_h_count = 0;
	for(i = 0; i < hole.p_count; i++) {
		if(hole.point[i].x == hole.point[i+1].x) {
			/* vertical */
			if(hole.point[i].y == hole.point[i+1].y)
				continue;
			vLine[vLineCount].x1 = hole_vline[hole_v_count].x1 = hole.point[i].x;
			vLine[vLineCount].x2 = hole_vline[hole_v_count].x2 = hole.point[i+1].x;
			vLine[vLineCount].y1 = hole_vline[hole_v_count].y1 = hole.point[i].y;
			vLine[vLineCount].y2 = hole_vline[hole_v_count].y2 = hole.point[i+1].y;
			if(hole.point[i+1].y > hole.point[i].y)
				vLine[vLineCount].direction = hole_vline[hole_v_count].direction = -1;
			else
				vLine[vLineCount].direction = hole_vline[hole_v_count].direction = 1;
			
			vLine[vLineCount].type = -1;
			vLineCount++; hole_v_count++;
		}
		else {
			/* horizon */
			if(hole.point[i].x == hole.point[i+1].x)
				continue;
			hLine[hLineCount].x1 = hole_hline[hole_h_count].x1 = hole.point[i].x;
			hLine[hLineCount].x2 = hole_hline[hole_h_count].x2 = hole.point[i+1].x;
			hLine[hLineCount].y1 = hole_hline[hole_h_count].y1 = hole.point[i].y;
			hLine[hLineCount].y2 = hole_hline[hole_h_count].y2 = hole.point[i+1].y;
			if(hole.point[i+1].x > hole.point[i].x)
				hLine[hLineCount].direction = hole_hline[hole_h_count].direction = -1;
			else
				hLine[hLineCount].direction = hole_hline[hole_h_count].direction = 1;

			hLine[hLineCount].type = -1;
			hLineCount++; hole_h_count++;
		}
	}
	/* cover */
	tmp_xy = 0;
	for(i = 0; i < cover.p_count; i++) {
		tmp_xy += cover.point[i].x * cover.point[i+1].y;
		tmp_xy -= cover.point[i].y * cover.point[i+1].x;
	}
	
	cover.area = tmp_xy;
	if(cover.area < 0) {
		cover.area *= -1;
		/*
		Point tmp_point[60];
		for(i = 0, j = cover.p_count; j >= 0; i++, j--) {
			tmp_point[i] = cover.point[j];
		}
		for(i = 0; i <= cover.p_count; i++) {
			cover.point[i] = tmp_point[i];
		}
		*/
	}

	cover_v_count = cover_h_count = 0;
	for(i = 0; i < cover.p_count; i++) {
		if(cover.point[i].x == cover.point[i+1].x) {
			if(cover.point[i].y == cover.point[i+1].y)
				continue;
			/* vertical */
			vLine[vLineCount].x1 = cover_vline[cover_v_count].x1 = cover.point[i].x;
			vLine[vLineCount].x2 = cover_vline[cover_v_count].x2 = cover.point[i+1].x;
			vLine[vLineCount].y1 = cover_vline[cover_v_count].y1 = cover.point[i].y;
			vLine[vLineCount].y2 = cover_vline[cover_v_count].y2 = cover.point[i+1].y;
			if(cover.point[i+1].y > cover.point[i].y)
				vLine[vLineCount].direction = cover_vline[cover_v_count].direction = -1;
			else
				vLine[vLineCount].direction = cover_vline[cover_v_count].direction = 1;

			vLine[vLineCount].type = 1;
			vLineCount++; cover_v_count++;
		}
		else {
			if(cover.point[i].x == cover.point[i+1].x)
				continue;
			/* horizon */
			hLine[hLineCount].x1 = cover_hline[cover_h_count].x1 = cover.point[i].x;
			hLine[hLineCount].x2 = cover_hline[cover_h_count].x2 = cover.point[i+1].x;
			hLine[hLineCount].y1 = cover_hline[cover_h_count].y1 = cover.point[i].y;
			hLine[hLineCount].y2 = cover_hline[cover_h_count].y2 = cover.point[i+1].y;
			if(cover.point[i+1].x > cover.point[i].x)
				hLine[hLineCount].direction = cover_hline[cover_h_count].direction = -1;
			else
				hLine[hLineCount].direction = cover_hline[cover_h_count].direction = 1;

			hLine[hLineCount].type = 1;
			hLineCount++; cover_h_count++;
		}
	}
}