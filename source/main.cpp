#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#define SECTIONS_IN_BLOCK 8
#define MAX_SIZE 500

struct CommandParameters;
struct AttributeList;
struct SelectorList;
struct SectionList;
struct BlockList;
template<typename T> class DoubleLinkedList;
class myString;

class myString {
private:
	char* str;

public:
	myString() : str(nullptr) {}

	myString(char c) {
		str = new char[2];
		str[0] = c;
		str[1] = '\0';
	}

	myString(const char* string) {
		str = new char[strlen(string) + 1];
		strcpy(str, string);
	}

	myString(const myString& other) {
		str = new char[strlen(other.str) + 1];
		strcpy(str, other.str);
	}

	myString& operator=(const myString& other) {
		str = new char[strlen(other.str) + 1];
		strcpy(str, other.str);
		return *this;
	}

	char operator[](const int index) {
		return str[index];
	}

	int length() const {
		return strlen(str);
	}

	friend std::ostream& operator<<(std::ostream& os, const myString& str) {
		os << str.c_str();
		return os;
	}

	myString operator+(const myString& other) const {
		myString result;
		result.str = new char[length() + other.length() + 1];
		strcpy(result.str, str);
		strcat(result.str, other.str);
		return result;
	}

	bool operator!=(myString& str2) {
		return strcmp(str, str2.str);
	}

	myString operator+(char c) const {
		myString result;
		result.str = new char[length() + 2];
		strcpy(result.str, str);
		result.str[length()] = c;
		result.str[length() + 1] = '\0';
		return result;
	}

	bool operator==(const myString& other) const {
		return strcmp(str, other.str) == 0;
	}

	bool operator!() const {
		return str == nullptr;
	}

	bool isEmpty() const {
		return length() == 0;
	}

	bool operator!=(const char* str) const {
		return !(*this == str);
	}

	myString& operator+=(const myString& other) {
		char* new_str = new char[length() + other.length() + 1];
		strcpy(new_str, str);
		strcat(new_str, other.str);
		delete[] str;
		str = new_str;
		return *this;
	}

	myString& operator+=(char c) {
		char* new_str = new char[length() + 2];
		strcpy(new_str, str);
		new_str[length()] = c;
		new_str[length() + 1] = '\0';
		delete[] str;
		str = new_str;
		return *this;
	}

	const char* c_str() const {
		return str;
	}

	~myString() {
		delete[] str;
	}
};

struct AttributeList {
	myString name = "";
	myString value = "";
	AttributeList* next = NULL;
	AttributeList* prev = NULL;
};

struct SelectorList {
	myString name = "";
	SelectorList* next = NULL;
	SelectorList* prev = NULL;
};

struct SectionList {
	DoubleLinkedList<SelectorList>* selectors;
	DoubleLinkedList<AttributeList>* attributes;
	SectionList* next = NULL;
	SectionList* prev = NULL;
};

struct BlockList {
	SectionList* sections = new SectionList[SECTIONS_IN_BLOCK];
	BlockList* next = NULL;
	BlockList* prev = NULL;
	int sectionsCounter = 0;
};

struct CommandParameters {
	char character;
	myString input = "";
	myString output = "";
	myString firstParameter = "";
	myString secondParameter = "";
	myString thirdParameter = "";
	myString sectionNumber = "";
	bool isFirstParamInt = false;
	bool isThirdParamInt = false;
};

template<typename T>
class DoubleLinkedList {
public:
	T* head;
	T* tail;

public:
	DoubleLinkedList() : head(nullptr), tail(nullptr) {}

	void addNode(T* newNode) {
		if (!head) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	}

	void removeNode(T* nodeToRemove) {
		if (!head) {
			return;
		}
		if (head == nodeToRemove) {
			head = head->next;
			if (head) {
				head->prev = nullptr;
			}
			else {
				tail = nullptr;
			}
			delete nodeToRemove;
			return;
		}
		T* currentNode = head->next;
		while (currentNode) {
			if (currentNode == nodeToRemove) {
				currentNode->prev->next = currentNode->next;
				if (currentNode->next) {
					currentNode->next->prev = currentNode->prev;
				}
				else {
					tail = currentNode->prev;
				}
				delete nodeToRemove;
				return;
			}
			currentNode = currentNode->next;
		}
	}

	T* getFirstNode() const {
		return head;
	}

	T* getLastNode() const {
		return tail;
	}

	~DoubleLinkedList() {
		T* currentNode = head;
		while (currentNode) {
			T* nextNode = currentNode->next;
			delete currentNode;
			currentNode = nextNode;
		}
	}
};

myString remove_spaces(myString& str) {
	myString trimmed_str = "";
	int start = 0;
	int end = str.length() - 1;
	while (start <= end && str[start] == ' ') {
		start++;
	}

	while (end >= start && str[end] == ' ') {
		end--;
	}

	for (int i = start; i <= end; i++) {
		trimmed_str += str[i];
	}

	return trimmed_str;
}

int myStringToInt(myString& str) {
	int result = 0;
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] >= '0' && str[i] <= '9') {
			result = result * 10 + (str[i] - '0');
		}
	}
	return result;
}

bool isDigit(const char arr[]) {
	int i = 0;
	while (i < strlen(arr)) {
		if (!isdigit(arr[i]))
			return false;
		i++;
	}
	return true;
}

void removeDuplicates(DoubleLinkedList<AttributeList>* attributeList) {
	if (!attributeList || !attributeList->head) {
		return;
	}

	AttributeList* lastNode = attributeList->getLastNode();
	while (lastNode) {
		AttributeList* currentNode = attributeList->head;
		while (currentNode && currentNode != lastNode) {
			if (currentNode->name == lastNode->name) {
				AttributeList* temp = currentNode;
				if (currentNode == attributeList->head) {
					attributeList->head = currentNode->next;
				}
				else {
					currentNode->prev->next = currentNode->next;
				}
				if (currentNode->next) {
					currentNode->next->prev = currentNode->prev;
				}
				currentNode = currentNode->next;
				delete temp;
			}
			else {
				currentNode = currentNode->next;
			}
		}
		lastNode = lastNode->prev;
	}
}

void parseSelectors(myString& selectorInput, DoubleLinkedList<SelectorList>* selectorList) {
	myString selectorName = "";
	int i = 0;
	while (i < selectorInput.length()) {
		if ((selectorInput[i] == ',' || (i == selectorInput.length() - 1 && !selectorName.isEmpty()))) {
			if (selectorInput.length() - 1 == i) selectorName += selectorInput[i];
			SelectorList* newSelector = new SelectorList;
			newSelector->name = remove_spaces(selectorName);
			selectorList->addNode(newSelector);
			selectorName = "";
		}
		else selectorName += selectorInput[i];
		i++;
	}
}

void parseAttributes(myString& attributeInput, DoubleLinkedList<AttributeList>* attributeList) {
	myString temp = "";
	int i = 0;
	while (i < attributeInput.length()) {
		if (attributeInput[i] == ';' || (i == attributeInput.length() - 1 && !temp.isEmpty())) {
			if (attributeInput[i] != ';' && i == attributeInput.length() - 1) temp += attributeInput[i];
			myString attrName = "";
			myString attrValue = "";
			bool beginningOfValue = false;

			for (int j = 0; j < temp.length(); j++) {
				if (temp[j] == ':') beginningOfValue = true;
				else if (temp[j] == ';') beginningOfValue = false;
				else if (beginningOfValue) attrValue += temp[j];
				else attrName += temp[j];
			}

			AttributeList* newAttr = new AttributeList;
			newAttr->name = attrName;
			newAttr->value = attrValue;
			attributeList->addNode(newAttr);
			temp = "";
		}
		else temp += attributeInput[i];
		i++;
	}
}

void parseSection(myString& selectorInput, myString& attributeInput, DoubleLinkedList<BlockList>& blockList) {
	BlockList* currentBlock = blockList.getLastNode();
	SectionList currentSection = currentBlock->sections[currentBlock->sectionsCounter];
	DoubleLinkedList<SelectorList>* selectorList = new DoubleLinkedList<SelectorList>;
	DoubleLinkedList<AttributeList>* attributeList = new DoubleLinkedList<AttributeList>;

	if (currentBlock->sectionsCounter == SECTIONS_IN_BLOCK - 1) {
		BlockList* newBlock = new BlockList;
		blockList.addNode(newBlock);
		currentBlock = blockList.getLastNode();
		currentSection = currentBlock->sections[currentBlock->sectionsCounter];

	}

	parseSelectors(selectorInput, selectorList);
	parseAttributes(attributeInput, attributeList);

	currentSection.attributes = attributeList;
	currentSection.selectors = selectorList;
	currentBlock->sections[currentBlock->sectionsCounter] = currentSection;
	currentBlock->sectionsCounter += 1;
}

void parseCSS(DoubleLinkedList<BlockList>& blockList) {
	char character;
	myString selectorInput = "";
	myString attributeInput = "";
	myString input = "";
	bool beginningOfAttributes = false;

	while (std::cin >> character >> std::noskipws) {
		switch (character) {
		case '\n':
		case '\t':
			break;
		case '{':
			beginningOfAttributes = true;
			break;
		case '}':
			parseSection(selectorInput, attributeInput, blockList);
			selectorInput = "";
			attributeInput = "";
			input = "";
			beginningOfAttributes = false;
			break;
		default:
			if (beginningOfAttributes) attributeInput += character;
			else selectorInput += character;
			input += character;
			break;
		}

		if (input == "????") return;
		if (character == EOF) return;
	}
}

myString getAmountOfSections(DoubleLinkedList<BlockList>& blockList) {
	int secCounter = 0;
	char secCounterChar[MAX_SIZE];
	BlockList* currentBlock = blockList.head;

	while (currentBlock) {
		secCounter += currentBlock->sectionsCounter;
		currentBlock = currentBlock->next;
	}

	sprintf(secCounterChar, "%d", secCounter);
	myString returnString = { "? == " };
	returnString += secCounterChar;
	return returnString;
}

myString getAmountOfSelectorsInSectionI(DoubleLinkedList<BlockList>& blockList, myString sectionNum) {
	int sectionNumber = myStringToInt(sectionNum);
	int currentSection = 0;
	char sectionNumberChar[MAX_SIZE];
	char selectorsCounterChar[MAX_SIZE];

	for (BlockList* currentBlock = blockList.getFirstNode(); currentBlock; currentBlock = currentBlock->next) {
		if (!currentBlock->sections) continue;
		for (int i = 0; i < currentBlock->sectionsCounter; i++) {
			currentSection++;
			if (currentSection == sectionNumber) {
				int selectorsCounter = 0;
				if (!currentBlock->sections[i].selectors) continue;
				for (SelectorList* currentSelector = currentBlock->sections[i].selectors->getFirstNode(); currentSelector; currentSelector = currentSelector->next) {
					selectorsCounter++;
				}

				sprintf(sectionNumberChar, "%d", sectionNumber);
				sprintf(selectorsCounterChar, "%d", selectorsCounter);
				myString returnString = sectionNumberChar;
				returnString += { ",S,? == " };
				returnString += selectorsCounterChar;
				return returnString;
			}
		}
	}
	return "";
}

myString getAmountOfAttributesInSectionI(DoubleLinkedList<BlockList>& blockList, myString sectionNum) {
	int sectionNumber = myStringToInt(sectionNum);
	int currentSection = 0;
	char sectionNumberChar[MAX_SIZE];
	char attributesCounterChar[MAX_SIZE];

	for (BlockList* currentBlock = blockList.getFirstNode(); currentBlock; currentBlock = currentBlock->next) {
		if (!currentBlock->sections) continue;
		for (int i = 0; i < currentBlock->sectionsCounter; i++) {
			currentSection++;
			if (currentSection == sectionNumber) {
				SectionList& SectionList = currentBlock->sections[i];
				AttributeList* attr = SectionList.attributes->getFirstNode();
				removeDuplicates(SectionList.attributes);
				int counterAttributes = 0;
				if (SectionList.attributes) {
					for (AttributeList* attr = SectionList.attributes->getFirstNode(); attr; attr = attr->next) {
						counterAttributes++;
					}
				}
				else {
					return "";
				}

				sprintf(sectionNumberChar, "%d", sectionNumber);
				sprintf(attributesCounterChar, "%d", counterAttributes);
				myString returnString = sectionNumberChar;
				returnString += { ",A,? == " };
				returnString += attributesCounterChar;
				return returnString;
			}
		}
	}
	return "";
}

myString getJselectorForIsection(DoubleLinkedList<BlockList>& blockList, myString selectorNum, myString sectionNum) {
	int sectionNumber = myStringToInt(sectionNum);
	int selectorNumber = myStringToInt(selectorNum);
	int currentSection = 0;

	for (BlockList* currentBlock = blockList.getFirstNode(); currentBlock; currentBlock = currentBlock->next) {
		if (!currentBlock->sections) continue;
		for (int i = 0; i < currentBlock->sectionsCounter; i++) {
			currentSection++;
			if (currentSection == sectionNumber) {
				if (currentBlock->sections[i].selectors == nullptr) return "";

				SelectorList* selector = currentBlock->sections[i].selectors->getFirstNode();
				int currentSelector = 0;
				while (selector) {
					currentSelector++;
					if (currentSelector == selectorNumber) {
						if (selector == nullptr) return "";

						char sectionNumberChar[MAX_SIZE];
						char selectorNumberChar[MAX_SIZE];
						sprintf(sectionNumberChar, "%d", sectionNumber);
						sprintf(selectorNumberChar, "%d", selectorNumber);
						myString returnString = sectionNumberChar;
						returnString += { ",S," };
						returnString += selectorNumberChar;
						returnString += {" == "};
						returnString += selector->name;
						return returnString;
					}
					selector = selector->next;
				}
				return "";
			}
		}
	}
	return "";
}

myString getAttributeValueForSection(DoubleLinkedList<BlockList>& blockList, myString attrName, myString sectionNum) {
	int sectionNumber = myStringToInt(sectionNum);
	int currentSection = 0;

	for (BlockList* currentBlock = blockList.getFirstNode(); currentBlock; currentBlock = currentBlock->next) {
		if (!currentBlock->sections) continue;
		for (int i = 0; i < currentBlock->sectionsCounter; i++) {
			currentSection++;
			if (currentSection == sectionNumber) {
				SectionList& SectionList = currentBlock->sections[i];
				if (!SectionList.attributes) continue;
				AttributeList* attr = SectionList.attributes->getFirstNode();
				while (attr) {
					if (!attr->name || !attr->value) continue;
					if (attr->name == attrName) {
						char sectionNumberChar[MAX_SIZE];
						sprintf(sectionNumberChar, "%d", sectionNumber);
						myString returnString = sectionNumberChar;
						returnString += { ",A," };
						returnString += attrName;
						returnString += {" =="};
						returnString += attr->value;
						return returnString;
					}
					attr = attr->next;
				}
			}
		}
	}
	return "";
}

myString getAttributeOccurrences(DoubleLinkedList<BlockList>& blockList, myString attributeName) {
	int occurrencesCounter = 0;
	char occurrencesCounterChar[MAX_SIZE];

	for (BlockList* currentBlock = blockList.getFirstNode(); currentBlock; currentBlock = currentBlock->next) {
		if (!currentBlock->sections) continue;
		for (int i = 0; i < currentBlock->sectionsCounter; i++) {
			SectionList* currentSection = &(currentBlock->sections[i]);
			if (!currentSection->attributes) continue;

			for (AttributeList* currentAttribute = currentSection->attributes->getFirstNode(); currentAttribute; currentAttribute = currentAttribute->next) {
				if (currentAttribute->name == attributeName) {
					occurrencesCounter++;
					break;
				}
			}
		}
	}

	sprintf(occurrencesCounterChar, "%d", occurrencesCounter);
	myString returnString = attributeName;
	returnString += { ",A,? == " };
	returnString += occurrencesCounterChar;
	return returnString;
}

myString getSelectorOccurrences(DoubleLinkedList<BlockList>& blockList, myString selectorName) {
	int occurrencesCounter = 0;
	char occurrencesCounterChar[MAX_SIZE];

	for (BlockList* currentBlock = blockList.getFirstNode(); currentBlock; currentBlock = currentBlock->next) {
		for (int i = 0; i < currentBlock->sectionsCounter; i++) {
			SectionList* currentSection = &(currentBlock->sections[i]);

			if (currentSection->selectors) {
				for (SelectorList* currentSelector = currentSection->selectors->getFirstNode(); currentSelector; currentSelector = currentSelector->next) {
					if (currentSelector && currentSelector->name == selectorName) {
						occurrencesCounter++;
					}
				}
			}
		}
	}

	sprintf(occurrencesCounterChar, "%d", occurrencesCounter);
	myString returnString = selectorName;
	returnString += { ",S,? == " };
	returnString += occurrencesCounterChar;
	return returnString;
}

myString getAttributeValueForSelector(DoubleLinkedList<BlockList>& blockList, myString attributeName, myString selectorName) {
	myString attributeValue = "";
	bool flag1 = false;
	bool flag2 = false;

	for (BlockList* currentBlock = blockList.getFirstNode(); currentBlock; currentBlock = currentBlock->next) {
		for (int i = 0; i < currentBlock->sectionsCounter; i++) {
			SectionList* currentSection = &(currentBlock->sections[i]);

			if (currentSection->selectors) {
				SelectorList* lastMatchingSelector = nullptr;

				for (SelectorList* currentSelector = currentSection->selectors->getFirstNode(); currentSelector; currentSelector = currentSelector->next) {
					if (currentSelector && currentSelector->name == selectorName) {
						lastMatchingSelector = currentSelector;
						flag1 = true;
					}
				}

				if (lastMatchingSelector && currentSection->attributes) {
					for (AttributeList* currentAttribute = currentSection->attributes->getFirstNode(); currentAttribute; currentAttribute = currentAttribute->next) {
						if (currentAttribute && currentAttribute->name == attributeName) {
							attributeValue = currentAttribute->value;
							flag2 = true;
						}
					}
				}
			}
		}
	}
	if (flag1 && flag2) {
		myString returnString = selectorName;
		returnString += { ",E," };
		returnString += attributeName;
		returnString += { " ==" };
		returnString += attributeValue;
		return returnString;
	}
	else return "";
}

myString deleteSection(DoubleLinkedList<BlockList>& blockList, myString sectionNum) {
	int sectionNumber = myStringToInt(sectionNum);
	int currentSection = 0;
	char sectionNumberChar[MAX_SIZE];

	for (BlockList* currentBlock = blockList.getFirstNode(); currentBlock; currentBlock = currentBlock->next) {
		if (!currentBlock->sections) continue;
		for (int i = 0; i < currentBlock->sectionsCounter; i++) {
			currentSection++;
			if (currentSection == sectionNumber) {
				if (currentBlock->sections[i].selectors) {
					delete currentBlock->sections[i].selectors;
					currentBlock->sections[i].selectors = nullptr;
				}

				if (currentBlock->sections[i].attributes) {
					delete currentBlock->sections[i].attributes;
					currentBlock->sections[i].attributes = nullptr;
				}

				for (int j = i; j < currentBlock->sectionsCounter - 1; j++) {
					currentBlock->sections[j] = currentBlock->sections[j + 1];
				}

				currentBlock->sectionsCounter--;
				sprintf(sectionNumberChar, "%d", sectionNumber);
				myString returnString = sectionNumberChar;
				returnString += { ",D,* == deleted" };
				return returnString;
			}
		}
	}
	return "";
}

myString deleteAttributeFromSection(DoubleLinkedList<BlockList>& blockList, myString attributeName, myString sectionNum) {
	int sectionNumber = myStringToInt(sectionNum);
	int currentSection = 0;
	char sectionNumberChar[MAX_SIZE];

	for (BlockList* currentBlock = blockList.getFirstNode(); currentBlock; currentBlock = currentBlock->next) {
		if (!currentBlock->sections) continue;
		for (int i = 0; i < currentBlock->sectionsCounter; i++) {
			if (++currentSection != sectionNumber) continue;
			if (!currentBlock->sections[i].attributes) continue;

			AttributeList* currentAttribute = currentBlock->sections[i].attributes->getFirstNode();
			while (currentAttribute) {
				if (currentAttribute->name == attributeName) {
					AttributeList* nextAttribute = currentAttribute->next;
					currentBlock->sections[i].attributes->removeNode(currentAttribute);
					currentAttribute = nextAttribute;
				}
				else {
					currentAttribute = currentAttribute->next;
				}
			}

			if (!currentBlock->sections[i].attributes->head) {
				SectionList* nextSection = currentBlock->sections[i].next;
				if (i == 0) {
					currentBlock->sections = nextSection;
					if (nextSection) nextSection->prev = NULL;
				}
				else {
					currentBlock->sections[i - 1].next = nextSection;
					if (nextSection) nextSection->prev = &currentBlock->sections[i - 1];
				}
				if (nextSection) {
					currentBlock->sections[i] = *nextSection;
					currentBlock->sections[i].prev = nextSection->prev;
					currentBlock->sections[i].next = nextSection->next;
					if (currentBlock->sections[i].prev) {
						currentBlock->sections[i].prev->next = &currentBlock->sections[i];
					}
					if (currentBlock->sections[i].next) {
						currentBlock->sections[i].next->prev = &currentBlock->sections[i];
					}
				}
				currentBlock->sectionsCounter--;
			}

			sprintf(sectionNumberChar, "%d", sectionNumber);
			myString returnString = sectionNumberChar;
			returnString += { ",D," };
			returnString += attributeName;
			returnString += { " == deleted" };
			return returnString;
		}
	}
	return "";
}

void processParameters(DoubleLinkedList<BlockList>& blockList, CommandParameters& cmd) {
	myString temp = "";
	cmd.firstParameter = "";
	cmd.secondParameter = "";
	cmd.thirdParameter = "";
	int paramIndex = 1;
	for (int i = 0; i <= cmd.input.length(); i++) {
		if (cmd.input[i] == ',' || i == cmd.input.length()) {
			switch (paramIndex) {
			case 1:
				cmd.firstParameter = remove_spaces(temp);
				cmd.isFirstParamInt = isDigit(cmd.firstParameter.c_str());
				if (cmd.isFirstParamInt) cmd.sectionNumber = cmd.firstParameter;
				paramIndex++;
				break;
			case 2:
				cmd.secondParameter = remove_spaces(temp);
				paramIndex++;
				break;
			case 3:
				cmd.thirdParameter = remove_spaces(temp);
				cmd.isThirdParamInt = isDigit(cmd.thirdParameter.c_str());
				paramIndex++;
				break;
			default:
				break;
			}
			temp = "";
		}
		else {
			temp += cmd.input[i];
		}
	}
}

void handleDCommand(DoubleLinkedList<BlockList>& blockList, CommandParameters& cmd) {
	if (cmd.isFirstParamInt) {
		if (cmd.thirdParameter == "*") {
			cmd.output += deleteSection(blockList, cmd.sectionNumber);
		}
		else {
			cmd.output += deleteAttributeFromSection(blockList, cmd.thirdParameter, cmd.sectionNumber);
		}
	}
}

void handleECommand(DoubleLinkedList<BlockList>& blockList, CommandParameters& cmd) {
	if (!cmd.isFirstParamInt && !cmd.isThirdParamInt) {
		cmd.output += getAttributeValueForSelector(blockList, cmd.thirdParameter, cmd.firstParameter);
	}
}

void handleSCommand(DoubleLinkedList<BlockList>& blockList, CommandParameters& cmd) {
	if (cmd.thirdParameter == "?") {
		if (cmd.isFirstParamInt) {
			cmd.output += getAmountOfSelectorsInSectionI(blockList, cmd.sectionNumber);
		}
		else {
			cmd.output += getSelectorOccurrences(blockList, cmd.firstParameter);
		}
	}
	else if (cmd.isThirdParamInt && cmd.isFirstParamInt) {
		cmd.output += getJselectorForIsection(blockList, cmd.thirdParameter, cmd.sectionNumber);
	}
}

void handleACommand(DoubleLinkedList<BlockList>& blockList, CommandParameters& cmd) {
	if (cmd.thirdParameter == "?") {
		if (cmd.isFirstParamInt) {
			cmd.output += getAmountOfAttributesInSectionI(blockList, cmd.sectionNumber);
		}
		else {
			cmd.output += getAttributeOccurrences(blockList, cmd.firstParameter);
		}
	}
	else if (cmd.isFirstParamInt && !cmd.isThirdParamInt) {
		cmd.output += getAttributeValueForSection(blockList, cmd.thirdParameter, cmd.sectionNumber);
	}
}

void processCommand(DoubleLinkedList<BlockList>& blockList, CommandParameters& cmd) {
	char cmdType = cmd.secondParameter[0];

	switch (cmdType) {
	case 'S':
		handleSCommand(blockList, cmd);
		break;
	case 'A':
		handleACommand(blockList, cmd);
		break;
	case 'E':
		handleECommand(blockList, cmd);
		break;
	case 'D':
		handleDCommand(blockList, cmd);
		break;
	default:
		cmd.output += "";
		break;
	}
}

void parseCommands(DoubleLinkedList<BlockList>& blockList, CommandParameters& cmd, bool flag) {
	if ((cmd.character == '\n' || cmd.character == ' ' || cmd.character == '\t' || cmd.character == EOF || flag)) {
		if (cmd.input == "????") {
			cmd.input = "";
		}
		else if (cmd.input == "****") {
			parseCSS(blockList);
			cmd.input = "";
		}
		else if (cmd.input == "?") {
			cmd.output += getAmountOfSections(blockList);
			cmd.input = "";
		}
		else {
			processParameters(blockList, cmd);
			processCommand(blockList, cmd);
		}
		cmd.output += '<';
		cmd.input = "";
	}
	else if (cmd.character != '\n' && cmd.character != ' ' && cmd.character != '\t' && !flag) {
		cmd.input += cmd.character;
	}
}

void printOutput(CommandParameters& cmd, bool& flag) {
	int i = 0;
	while (i < cmd.output.length()) {
		char c = cmd.output[i];
		if (c == '\n' || c == '<' || c == '/' || c == '\t') {
			if (c == '<' && i != 0 && flag) {
				std::cout << '\n';
				flag = false;
			}
			i++;
			continue;
		}
		std::cout << c;
		flag = true;
		i++;
	}
}

int main() {
	CommandParameters cmd;
	DoubleLinkedList<BlockList> blockList;
	BlockList* firstBlock = new BlockList;
	blockList.addNode(firstBlock);
	bool flag = false;

	parseCSS(blockList);

	while (std::cin >> cmd.character >> std::noskipws) {
		parseCommands(blockList, cmd, false);
	}

	printOutput(cmd, flag);

	return 0;
}