# CCTV 유지보수 예약 관리 프로그램

## 📌 프로젝트 개요

**CCTV 유지보수, 설치, 점검 업무를 위한 예약 관리 프로그램**입니다.

직관적인 사용자 인터페이스(UI)를 기반으로 고객 정보를 관리하고,

예약 등록 및 일정 조회를 효율적으로 수행할 수 있도록 설계되었습니다.

---

## 💡 주요 기능

### 1. 고객 관리 (EmployeePage)

- 고객사 정보 등록 및 리스트 관리
- 고객사별 고유 ID 생성 (UUID 기반)
- 검색 기능 제공

### 2. 예약 등록 (ScheduleRegisterPage)

- 캘린더 위젯 기반 날짜 선택
- 시간 선택 및 체크박스를 통한 완료 상태 표시
- 예약 시 시간당 최대 3개 제한 로직 적용
- 예약 완료 시 시각적 피드백 제공 (체크박스 + 색상)

### 3. 예약 조회 (ScheduleViewPage)

- 날짜별 예약 현황 테이블 형태로 표시
- 시간 기준 자동 정렬 기능
- 예약 내용 더블클릭 시 수정/삭제 가능
- 오늘 날짜 예약은 주황색으로 강조

---

## 🗂️ 폴더 및 코드 구조

```
├── main.cpp
├── widget.cpp
│   └── 메인 탭 관리 (고객 정보 / 일정 등록 / 일정 조회)
├── employeepage.cpp
│   └── 고객 정보 등록 및 리스트
├── scheduleregisterpage.cpp
│   └── 예약 등록 기능 및 충돌 검사
├── scheduleviewpage.cpp
│   └── Gantt Chart 시각화 및 상세 정보 확인
├── reservationitem.cpp
│   └── 예약 막대 객체 (더블클릭 팝업 기능 포함)
├── data.json
│   └── 예약 + 고객 정보 통합 저장
├── customers.json
│   └── 고객 정보 개별 저장

```

## 🛠️ 사용 기술 및 도구

| 항목 | 내용 |
| --- | --- |
| 언어 | C++ |
| 프레임워크 | Qt 6.x |
| UI 구성 | Qt Designer (QWidget, QTableWidget, QCalendarWidget 등) |
| 데이터 저장 | JSON 기반 파일 저장 (`customers.json`, `data.json`) |
| 기타 | UUID, Signal & Slot, QFile, QJsonDocument 등 |

---

## ✅ 실행 방법

1. Qt Creator에서 `.pro` 파일을 열어 빌드
2. 실행 시 `customers.json`, `data.json`은 자동 생성됨 (또는 기존 파일 사용 가능)
3. 예약 등록 및 고객 선택 후 저장 버튼으로 정보 반영
