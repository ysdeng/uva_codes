#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BinaryLen 20000
#define StringLen 5000
typedef struct Node{
	int color, pure;
	struct Node* node[4];
} Node;

Node* treeOne;
Node* treeTwo;
Node* treeResult;

char OneString[StringLen], TwoString[StringLen];
int OneBinary[BinaryLen], TwoBinary[BinaryLen];
int OneBinaryCount, TwoBinaryCount;

int Result[BinaryLen], ResultString[StringLen];

int CharToInt(char a);
void StringToBinary();

void BuildTree(Node* n, int index);
void BuildResultTree(Node* n1, Node* n2, Node* nR);
void CompressResultTree(Node* n);

void printNode(Node* n);
void BinaryToString();

void Destroy(Node* n);

int globalCount;

void init () {
	int i;

	treeOne = (Node*) malloc(sizeof(Node));
	treeTwo = (Node*) malloc(sizeof(Node));
	treeResult = (Node*) malloc(sizeof(Node));

	for(i = 0; i < 4; i++)
		treeResult->node[i] = treeOne->node[i] = treeTwo->node[i] = NULL;
	for(i = 0; i < BinaryLen; i++)
		Result[i] = 0;
	for(i = 0; i < StringLen; i++)
		ResultString[i] = 0;
}

int main() {
	int i, j, k;
	int testCase = 0;
	while(1) {
		init();

		scanf("%s%s", OneString, TwoString);
		if(CharToInt(OneString[0]) == 0 
			&& CharToInt(TwoString[0]) == 0)
			break;

		StringToBinary();
		
		BuildResultTree(treeOne, treeTwo, treeResult);
		
		CompressResultTree(treeResult);

		Result[0] = 1;
		globalCount = 1;

		printNode(treeResult);
		
		BinaryToString();
		
		if(testCase) puts("");
		printf("Image %d:\n", ++testCase);
		int dd = 0;
		for(i = 0; i < globalCount; i++) {
			if(ResultString[i] > 0) dd++;
			if(dd) printf("%X", ResultString[i]);
		}
		puts("");

		Destroy(treeOne);
		Destroy(treeTwo);

	}
	return 0;
}

int CharToInt(char a) {
	int hex;
	if(a == '0') return 0;
	else if(a == '1') return 1;
	else if(a == '2') return 2;
	else if(a == '3') return 3;
	else if(a == '4') return 4;
	else if(a == '5') return 5;
	else if(a == '6') return 6;
	else if(a == '7') return 7;
	else if(a == '8') return 8;
	else if(a == '9') return 9;
	else if(a == 'A') return 10;
	else if(a == 'B') return 11;
	else if(a == 'C') return 12;
	else if(a == 'D') return 13;
	else if(a == 'E') return 14;
	else return 15;

}

void StringToBinary() {
	int tmpBinary[BinaryLen];
	int len;
	/* init all Binary Buf */
	int i, j, k;
	for(i = 0; i < BinaryLen; i++)
		OneBinary[i] = TwoBinary[i] = tmpBinary[i] = 0;

	len = strlen(OneString);
	for(i = 0, j = 0; i < len; i++, j+=4) {
		int xx = CharToInt(OneString[i]);
		tmpBinary[j] = xx >> 3 & 1;
		tmpBinary[j+1] = xx >> 2 & 1;
		tmpBinary[j+2] = xx >> 1 & 1;
		tmpBinary[j+3] = xx & 1;
	}
	int tmpCount = j;
	
	int start;
	for(i = 0, start = 0, k = 0; i < tmpCount; i++) {
		if(start) OneBinary[k++] = tmpBinary[i];
		else if(tmpBinary[i]) start = 1;
	}

	OneBinaryCount = k;

	globalCount = 0;
	BuildTree(treeOne, 0);

	len = strlen(TwoString);
	for(i = 0, j = 0; i < len; i++, j+=4) {
		int xx = CharToInt(TwoString[i]);
		tmpBinary[j] = xx >> 3 & 1;
		tmpBinary[j+1] = xx >> 2 & 1;
		tmpBinary[j+2] = xx >> 1 & 1;
		tmpBinary[j+3] = xx & 1;
	}
	tmpCount = j;
	for(i = 0, start = 0, k = 0; i < tmpCount; i++) {
		if(start) TwoBinary[k++] = tmpBinary[i];
		else if(tmpBinary[i]) start = 1;
	}
	TwoBinaryCount = k;

	globalCount = 0;
	BuildTree(treeTwo, 1);
}

void BuildTree(Node* n, int index) {
	if(n == NULL) return;

	if(index == 0)
		n->pure = OneBinary[globalCount++];
	else
		n->pure = TwoBinary[globalCount++];

	if(n->pure == 1) {
		if(index == 0)
			n->color = OneBinary[globalCount++];
		else
			n->color = TwoBinary[globalCount++];
		return;
	}
	else {
		int i, j;
		for(i = 0; i < 4; i++) {
			n->node[i] = (Node*)malloc(sizeof(Node));
			while(n->node[i] == NULL)
				n->node[i] = (Node*)malloc(sizeof(Node));
			for (j = 0; j < 4; j++) {
				n->node[i]->node[j] = NULL;
			}
		}

		for(i = 0; i < 4; i++)
			BuildTree((n->node[i]), index);
	}
	return;
}

void BuildResultTree(Node* n1, Node* n2, Node* nR) {
	if(n1 == NULL) return;
	if(n2 == NULL) return;
	if(nR == NULL) return;

	int i, j, k;
	if(n1->pure == 0 && n2->pure == 0) {
		int i, j;
		nR->pure = 0;
		for(i = 0; i < 4; i++) {
			nR->node[i] = (Node*)malloc(sizeof(Node));
			while(nR->node[i] == NULL)
				nR->node[i] = (Node*)malloc(sizeof(Node));
			for (j = 0; j < 4; j++) {
				nR->node[i]->node[j] = NULL;
			}
		}
		for(i = 0; i < 4; i++)
			BuildResultTree(n1->node[i], n2->node[i], nR->node[i]);
	}

	if(n1->pure == 1) {
		if(n2->pure == 1) {
			nR->pure = 1;
			nR->color = n1->color & n2->color;
			return;
		}
		if(n1->color == 1) {
			nR->pure = 0;
			for(i = 0; i < 4; i++)
				nR->node[i] = n2->node[i];
			return;
		}
		else {
			nR->pure = 1;
			nR->color = 0;
			return;
		}
	}

	if(n2->pure == 1) {
		if(n1->pure == 1) {
			nR->pure = 1;
			nR->color = n1->color & n2->color;
			return;
		}
		if(n2->color == 1) {
			nR->pure = 0;
			for(i = 0; i < 4; i++)
				nR->node[i] = n1->node[i];
			return;
		}
		else {
			nR->pure = 1;
			nR->color = 0;
			return;
		}
	}
}

void CompressResultTree(Node* n) {
	if(n == NULL) return;
	if(n->pure == 1) return;
	/* checkPure */
	if(n->node[0]->pure == 1 && n->node[1]->pure == 1
		&& n->node[2]->pure == 1 && n->node[3]->pure == 1) {

		if(n->node[0]->color == 0 && n->node[1]->color == 0
			&& n->node[2]->color == 0 && n->node[3]->color == 0) {
			n->color = 0;
			n->pure = 1;
			return;
		}
		if(n->node[0]->color == 1 && n->node[1]->color == 1
			&& n->node[2]->color == 1 && n->node[3]->color == 1) {
			n->color = 1;
			n->pure = 1;
			return;
		}
		return;
	}

	int i;
	for(i = 0; i < 4; i++)
		if(n->node[i]->pure == 0) {
			CompressResultTree(n->node[i]);
		}

	/* checkPure */
	if(n->node[0]->pure == 1 && n->node[1]->pure == 1
		&& n->node[2]->pure == 1 && n->node[3]->pure == 1) {
		if(n->node[0]->color == 0 && n->node[1]->color == 0
			&& n->node[2]->color == 0 && n->node[3]->color == 0) {
			n->color = 0;
			n->pure = 1;
			return;
		}
		if(n->node[0]->color == 1 && n->node[1]->color == 1
			&& n->node[2]->color == 1 && n->node[3]->color == 1) {
			n->color = 1;
			n->pure = 1;
			return;
		}
	}
}

void BinaryToString() {
	int i, j;
	
	int tmp[BinaryLen];
	for(i = 0; i < BinaryLen; i++) tmp[i] = 0;

	for(i = 0, j = BinaryLen-globalCount; i < globalCount; i++, j++) {
		tmp[j] = Result[i];
	}
	
	int cc = 0;
	for(i = 0, j = 0; i < BinaryLen; i += 4) {
		cc = 0;
		cc = 8*tmp[i] + 4*tmp[i+1] + 2*tmp[i+2] + tmp[i+3];
		ResultString[j++] = cc;
	}
	globalCount = j;
}

void printNode(Node* n) {
	if(n == NULL) return;

	Result[globalCount++] = n->pure;
	
	if(n->pure == 1) {
		Result[globalCount++] = n->color;
		return;
	}

	int i;
	for(i = 0; i < 4; i++)
		if(n->node[i] != NULL)
			printNode(n->node[i]);
}

void Destroy(Node* n) {
	if(n == NULL) return;

	int i;
	for(i = 0; i < 4; i++) {
		Destroy(n->node[i]);
	}
	free(n);
}