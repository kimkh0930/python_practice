﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TABLE_SIZE 10007
#define INPUT_SIZE 5000

typedef struct {
	int id; //키 값
	char name[20];
} Student;

void init(Student** hashTable) {
	for (int i = 0; i < TABLE_SIZE; i++) { //포인터에 널을 넣어 초기화
		hashTable[i] = NULL;
	}
}

void destructor(Student** hashTable) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable[i] != NULL) {
			free(hashTable[i]);
		}
	}
}

//해시 테이블 내 빈 공간을 선형 탐색으로 찾는다.
int findEmpty(Student** hashTable, int id) {
	int i = id % TABLE_SIZE;
	while (1) {
		if (hashTable[i % TABLE_SIZE] == NULL) {
			return i % TABLE_SIZE;
		}
		i++; //이미 차 있다면 1씩 더해가면서 넣어준다.
	}
}

// 특정 id값에 매칭되는 데이터를 해시 테이블 내에서 찾는다.
int search(Student** hashTable, int id) {
	int i = id % TABLE_SIZE;
	while (1) {
		if (hashTable[i % TABLE_SIZE] == NULL)return -1; //그 곳이 비어있다면 -1을 반환
		else if (hashTable[i % TABLE_SIZE]->id == id)return i;
		i++;
	}
}

//특정한 키 인덱스에 데이터를 삽입
void add(Student** hashTable, Student* input, int key) {
	hashTable[key] = input;
}

//해시 테이블에서 특정한 키의 데이터를 반환
Student* getValue(Student** hashTable, int key) {
	return hashTable[key];
}

//해시 테이블에 존재하는 모든 데이터를 출력
void show(Student** hashTable) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable[i] != NULL) {
			printf("키: [%d] 이름: [%s]\n", i, hashTable[i]->name);
		}
	}
}

int main(void) {
	Student** hashTable;
	hashTable = (Student**)malloc(sizeof(Student) * TABLE_SIZE);
	init(hashTable);

	for (int i = 0; i < INPUT_SIZE; i++) {
		Student* student = (Student*)malloc(sizeof(Student));
		student->id = rand() % 1000000; //랜덤과 나눗셈을 이용해 id 생성
		sprintf(student->name, "사람%d", student->id); 
		if (search(hashTable, student->id) == -1) { //중복 불가
			int index = findEmpty(hashTable, student->id);
			add(hashTable, student, index);
		}
	}

	show(hashTable);
	destructor(hashTable);
	system("pause");
	return 0;

}