6 7번 과제를 하나의 프로젝트에서 진행하였습니다.

1. 6번 과제-도전과제 2번까지 진행하였습니다.

	서로 다른 동작 로직을 수행해야한다고 하셔서 상속을 활용해야 함을 인지하였으나
	상태를 변경하면 동일한 Actor라도 각각 다른 행동을 하도록 구성할수 있을것이라는 발상을 시작으로
	enum이 언리얼 내에서 어떤식으로 구현이 가능한지 호기심이 생겨 아래와같이 구성하였습니다
		-Normal 상태일때 변수값에 따라서 지속적인 회전과 이동을 하도록 Tick 함수를 구성하였습니다.
		-Random 상태일때 Timer 동작에 따라 랜덤값을 return받아 매번 다른 방향으로 회전하도록 구성하였습니다.
		-Patrol  상태일때 시작지점에서 도착 지점까지 이동하며 이동을 마친후 Return 상태로 변경되며 기존 출발지점으로 돌아갑니다.

2. 7번 과제-도전과제2번까지 진행하였습니다.

	추가적인 변경점은 없습니다.
