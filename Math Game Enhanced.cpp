#include <iostream>
#include <string>

using namespace std;

enum enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };

enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

struct stQuestion {
	int Num1;
	int Num2;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswer;
	int PlayerAnswer;
	bool AnswerResult = false;
};

struct stQuiz {
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionsLevel QuestionsLevel;
	enOperationType OpType;
	short RightAnswers = 0;
	short WrongAnswers = 0;
	bool isPass;
};

int generateRandomNumber(int From, int To) {
	return rand() % (To - From + 1) + From;
}

short HowManyQuestions() {
	short Number;
	do {
		cout << "How Many Questions do you want to answer ?";
		cin >> Number;
		cout << endl;

	} while (Number < 0);

	return Number;
}

enQuestionsLevel ReadQuestionLevel() {

	short Chooser;
	cout << "Enter Questions Level [1] Easy, [2] Mid, [3] Hard, [4] Mix ? ";
	cin >> Chooser;

	switch (Chooser) {
	case 1:
		return enQuestionsLevel::Easy;
	case 2:
		return enQuestionsLevel::Med;
	case 3:
		return enQuestionsLevel::Hard;
	default:
		return enQuestionsLevel::Mix;
	}
}

enOperationType ReadOperationType() {
	short OpType;
	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> OpType;
	} while (OpType < 1 || OpType >5);
	return (enOperationType)OpType;
}

int ReadQuestionAnswer() {
	int Num;
	cin >> Num;
	return Num;
}

int SimpleCalculator(int Num1,int Num2, enOperationType OpType) {
	switch (OpType) {
	case enOperationType::Add:
		return Num1 + Num2;
	case enOperationType::Sub:
		return Num1 - Num2;
	case enOperationType::Mul:
		return Num1 * Num2;
	default:
		return Num1 / Num2;

	}
}

string GetOperationTypeSymbol(enOperationType OpType) {
	switch (OpType) {
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Div:
		return "/";
	case enOperationType::Mul:
		return "*";
	default:
		return "Mix";
	}
}

string GetQuestionsLevelText(enQuestionsLevel QuestionLevel) {
	string arrQuestionLevel[4] = {"Easy", "Med", "Hard", "Mix"};
	return arrQuestionLevel[QuestionLevel - 1];
}

string GetQuestionsOperationTypeText(enOperationType OpType) {
	string arrOperationType[5] = { "Add", "Sub", "Mul", "Div", "Mix"};
	return arrOperationType[OpType - 1];
}

stQuestion GenerateQuestion(enOperationType OperationType, enQuestionsLevel QuestionLevel) {
	stQuestion Question;

	

	if (OperationType == enOperationType::MixOp) {
		OperationType = (enOperationType)generateRandomNumber(1, 4);
	}

	if (QuestionLevel == enQuestionsLevel::Mix) {
		QuestionLevel = (enQuestionsLevel)generateRandomNumber(1, 3);
	}

	Question.OperationType = OperationType;
	
	
	switch (QuestionLevel) {
	case enQuestionsLevel::Easy:
		Question.Num1 = generateRandomNumber(1, 10);
		Question.Num2 = generateRandomNumber(1, 10);
		Question.CorrectAnswer = SimpleCalculator(Question.Num1, Question.Num2, OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	case enQuestionsLevel::Med:
		Question.Num1 = generateRandomNumber(10, 50);
		Question.Num2 = generateRandomNumber(10, 50);
		Question.CorrectAnswer = SimpleCalculator(Question.Num1, Question.Num2, OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	default:
		Question.Num1 = generateRandomNumber(50, 100);
		Question.Num2 = generateRandomNumber(50, 100);
		Question.CorrectAnswer = SimpleCalculator(Question.Num1, Question.Num2, OperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	}
}

stQuiz GenerateQuizzQuestions(stQuiz& Quizz){
	for (short QuestionNumber = 0;QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++) {
		Quizz.QuestionList[QuestionNumber] = GenerateQuestion(Quizz.OpType, Quizz.QuestionsLevel);
	}
	return Quizz;
}

void SetScreenColor(bool Result) {
	if (Result)
		system("color 2f");
	else
		system("color 4f");
}

void PrintQuestionInfo(stQuiz Quizz,short QuestionNum) {
	cout << "Question [" << QuestionNum + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
	cout << Quizz.QuestionList[QuestionNum].Num1 << endl;
	cout << Quizz.QuestionList[QuestionNum].Num2 << " " << GetOperationTypeSymbol(Quizz.QuestionList[QuestionNum].OperationType) << endl;
	cout << "__________________\n";
}

void CheckPlayerAnswer(stQuiz& Quizz, short QuestionNum) {

	if (Quizz.QuestionList[QuestionNum].CorrectAnswer == Quizz.QuestionList[QuestionNum].PlayerAnswer) {
		Quizz.QuestionList[QuestionNum].AnswerResult = true;
		cout << "Right Answer :-)\n\n\n";
		Quizz.RightAnswers++;
	}
	else{
		cout << "Wrong Answer :-(\n";
		cout << "The Right Answer is: " << Quizz.QuestionList[QuestionNum].CorrectAnswer << "\n\n\n";
		Quizz.WrongAnswers++;
		Quizz.QuestionList[QuestionNum].AnswerResult = false;
	}
	SetScreenColor(Quizz.QuestionList[QuestionNum].AnswerResult);

}

void AskAndCorrectQuestionsListAnswer(stQuiz& Quizz) {
	for (short QuestionNum = 0; QuestionNum < Quizz.NumberOfQuestions; QuestionNum++) {
		PrintQuestionInfo(Quizz, QuestionNum);
		Quizz.QuestionList[QuestionNum].PlayerAnswer = ReadQuestionAnswer();
		CheckPlayerAnswer(Quizz, QuestionNum);
	}
	Quizz.isPass = (Quizz.RightAnswers >= Quizz.WrongAnswers);
}

string GetPassOrFail(bool isPass) {
	if (isPass)
		return  "PASS :-)";
	else
		return "FAIL :-(";
}

void PrintQuizzResults(stQuiz Quizz) {
	cout << "_____________________________\n\n";
	cout << "Final Result is " << GetPassOrFail(Quizz.isPass) << endl;
	cout << "_____________________________\n\n";
	cout << "Number of Questions : " << Quizz.NumberOfQuestions << endl;
	cout << "Question Level      : " << GetQuestionsLevelText(Quizz.QuestionsLevel) << endl;
	cout << "Operation Type      : " << GetQuestionsOperationTypeText(Quizz.OpType) << endl;
	cout << "Number of Right Answers: " << Quizz.RightAnswers << endl;
	cout << "Number of Wrong Answers: " << Quizz.WrongAnswers << "\n\n";
	cout << "_____________________________\n\n";




}

void PlayMathGame() {
	stQuiz Quizz;
	Quizz.NumberOfQuestions = HowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOperationType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionsListAnswer(Quizz);
	PrintQuizzResults(Quizz);


}

void ResetScreen() {
	system("cls");
	system("color 0F");
}

void StartGame() {
	char PlayAgian = 'Y';
	do {
		ResetScreen();
		PlayMathGame();
		cout << "Do You Want To Play Agian ? Y/N ?";
		cin >> PlayAgian;
	} while (PlayAgian == 'Y' || PlayAgian == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();


}

