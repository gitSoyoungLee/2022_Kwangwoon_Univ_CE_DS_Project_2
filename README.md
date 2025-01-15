![image](https://github.com/user-attachments/assets/89da59b0-8325-4ad2-a42b-ecdd54e46940)# 2022_Kwangwoon_Univ_CE_DS_Project_2

> 2022년 광운대학교 데이터구조설계 2차 과제 구현 내용입니다.

본 프로젝트에서는 C++을 기반으로 FP-Growth와 B+ Tree를 이용하여 상품 추천 프로그램을 구현한다.

 이 프로그램은 장바구니 데이터에서 같이 구매한 상품들을 받아 FP-Growth를 구축한다. FP-Growth는 상품들의 연관성을 Tree 구조로 저장하고 있는 FP-Tree와 상품별 빈도수 및 정보, 해당 상품과 연결된 FP-Tree의 상품 노드들을 관리하는 Header Table로 구성된다.

  FP-Growth 구축 단계에서 연관된 상품들을 묶은 Frequent Pattern들은 SAVE 명령어를 통해 result.txt에 빈도수, 상품 순으로 저장한다. Frequent Pattern들이 저장된 result.txt는 BTLOAD 명령어를 통해 빈도수를 기준으로 B+ Tree에 저장이 된다. B+ Tree는 IndexNode와 DataNode로 구성된다. IndexNode는 DataNode
를 찾기 위한 Node이고 DataNode는 해당 빈도수를 가지는 Frequent Pattern들이 저장된 Node이다. 

  ![image](https://github.com/user-attachments/assets/3108a910-b01c-4d4c-8c97-1dcc050cd254)


# 사용법과 설명

'2022_DS_Project2_ver1.pdf' 파일을 따라 상품 데이터 파일을 market.txt에 저장하고, main.cpp를 실행하여 원하는 커맨드를 입력한다.
출력 결과는 result.txt에 저장된다.
자세한 요구 사항은 '2022_DS_Project2_ver1.pdf' 파일에서
로직과 테스트 결과는 `2021202039_DS_project2.pdf` 파일에서 확인할 수 있다.
