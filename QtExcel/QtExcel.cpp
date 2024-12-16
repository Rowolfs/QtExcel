#include "QtExcel.h"

QtExcel::QtExcel(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.rowEdit, &QLineEdit::textChanged, this, &QtExcel::editRow_textChanged);
	connect(ui.editSearch, &QLineEdit::textChanged, this, &QtExcel::editSearch_textChanged);
	connect(ui.search, &QPushButton::clicked, this, &QtExcel::search_clicked);
	connect(ui.Ascending, &QRadioButton::toggled, this, &QtExcel::onAscendingToggled);
	connect(ui.Descending, &QRadioButton::toggled, this, &QtExcel::onDescendingToggled);
	connect(ui.EmailRadioButton, &QRadioButton::toggled, this, &QtExcel::onEmailRadioButtonToggled);
	connect(ui.NameRadioButton, &QRadioButton::toggled, this, &QtExcel::onNameRadioButtonToggled);
	connect(ui.FamilyRadioButton, &QRadioButton::toggled, this, &QtExcel::onFamilyRadioButtonToggled);
	connect(ui.PhoneNumberradioButton, &QRadioButton::toggled, this, &QtExcel::onPhoneNumberradioButtonToggled);
	connect(ui.SurnamesRadioButton, &QRadioButton::toggled, this, &QtExcel::onSurnamesRadioButtonToggled);
	connect(ui.IdRadioButton, &QRadioButton::toggled, this, &QtExcel::onIdRadioButtonToggled);
	connect(ui.deleteDuplicates, &QPushButton::clicked, this, &QtExcel::on_DeleteDuplicates_clicked);

    table = new Table(&ui);
	users = QList<User*>();

}

QtExcel::~QtExcel()
{}


void QtExcel::on_setRow_clicked() {
    
    if (rowCount == 0) {
        table->setTableSize(1, 6);
    }
    else
    {
        table->setTableSize(rowCount, 6);
    }
    
	

	table->render();

    

}
void QtExcel::editRow_textChanged(const QString &text) {
    bool ok;
    rowCount = text.toInt(&ok);
    if (ok) {
        qDebug() << "Converted value" << rowCount;
    }
    else
    {
        qDebug() << "Conversion failed";

    }

}


QList<QString> convertIntListToStringList(const QList<int> intList) {
    QList<QString> stringList;
    for (int value : intList) {
        stringList.append(QString::number(value));
    }
    return stringList;
}

void QtExcel::on_fillRandom_clicked() {

	if (rowCount == 0)
	{
		on_setRow_clicked();
	}

	for (int i = 0; i < table->getRowCount(); i++)
	{

		if (i >= users.size()) {
			users.append(new User(i));
		}
		else
		{
			delete users[i];
			users[i] = new User(i);
		}
		table->fillRow(QList<QString> { QString::number(users[i]->getId()), users[i]->getName(), users[i]->getSurname(), users[i]->getFamily(), users[i]->getPhoneNumber(), users[i]->getEmail() }, i);
	}
	checkTableValues();
	table->render();

}





void QtExcel::checkTableValues() {

	

    for (int i = 0; i < table->getRowCount(); i++)
    {
        
		for (int j = 0; j < table->getColumnCount(); j++)
		{
			checkTableValue(table->getData()[i][j],i, j);
		}
		
    }



}


void QtExcel::on_minimum_clicked() {
	int min = INT_MAX;
	QRegularExpression phoneRegex("^\\+?\\d{10,15}$");
	for (int i = 0; i < table->getRowCount(); i++)
	{
		int ll = 0;
		QString phone = table->getData()[i][4];
		if (!phoneRegex.match(phone).hasMatch()) {
			continue;
		}
		for (int j = 1; j < phone.size(); j++)
		{
			try {
				ll += phone[j].digitValue();

			}
			catch (const std::exception& e) {

			}

		}
		if (ll < min) {
			min = ll;
		}
	}
	if (min == INT_MAX)
	{
		QMessageBox(QMessageBox::Icon::Information, "Minimum", "No numbers in table").exec();
		return;
	}
	else
	{
		QMessageBox(QMessageBox::Icon::Information, "Minimum", "Minimum sum of numbers in phone number is " + QString::number(min)).exec();
	}
}

void QtExcel::on_maximum_clicked() {
	int max = INT_MIN;
	QRegularExpression phoneRegex("^\\+?\\d{10,15}$");
	for (int i = 0; i < table->getRowCount(); i++)
	{
		int ll = 0;
		QString phone = table->getData()[i][4];
		if (!phoneRegex.match(phone).hasMatch()) {
			continue;
		}
		for (int j = 1; j < phone.size(); j++)
		{
			try {
				ll += phone[j].digitValue();
			}
			catch (const std::exception& e) {
				// Обработка исключения
			}
		}
		if (ll > max) {
			max = ll;
		}
	}
	if (max == INT_MIN)
	{
		QMessageBox(QMessageBox::Icon::Information, "Maximum", "No numbers in table").exec();
		return;
	}
	else
	{
		QMessageBox(QMessageBox::Icon::Information, "Maximum", "Maximum sum of numbers in phone number is " + QString::number(max)).exec();
	}
}

void QtExcel::on_average_clicked() {
	int totalSum = 0;
	int validRows = 0;
	QRegularExpression phoneRegex("^\\+?\\d{10,15}$");
	for (int i = 0; i < table->getRowCount(); i++)
	{
		int ll = 0;
		QString phone = table->getData()[i][4];
		if (!phoneRegex.match(phone).hasMatch()) {
			continue;
		}
		for (int j = 1; j < phone.size(); j++)
		{
			try {
				ll += phone[j].digitValue();
			}
			catch (const std::exception& e) {
				// Обработка исключения
			}
		}
		totalSum += ll;
		validRows++;
	}
	if (validRows == 0)
	{
		QMessageBox(QMessageBox::Icon::Information, "Average", "No numbers in table").exec();
		return;
	}
	int answer = totalSum / validRows;
	QMessageBox(QMessageBox::Icon::Information, "Average", "Average sum of numbers in phone number is " + QString::number(answer)).exec();
}
void QtExcel::search_clicked() {
	int count = 0;
	QString answer = "";
	for (int i = 0; i < table->getRowCount(); i++)
	{
		for (int j = 0; j < table->getColumnCount(); j++)
		{
			
			QString ll = table->getCell(i, j);
			if (ll == searchVall) {
				count++;
				answer += QString("%1:%2\n").arg(i + 1).arg(j + 1);
			}
			
		}
	}
	if (count == 0)
	{
		QMessageBox(QMessageBox::Icon::Information, "Search", "No numbers in table").exec();
		return;
	}
	QMessageBox(QMessageBox::Icon::Information, "Search", "Value " + searchVall + " found " + QString::number(count) + " times" +"\n"+answer).exec();
	table->render();
}

void QtExcel::onAscendingToggled() {

	isAscendingSort = true;
}

void QtExcel::onDescendingToggled() {

	isAscendingSort = false;
}

void QtExcel::on_sort_clicked() {







	if (isIdsort) {


		std::sort(users.begin(), users.end(), [this](User* a, User* b) {
			if (isAscendingSort) {
				return a->getId() < b->getId();
			}
			else
			{
				return a->getId() > b->getId();
			}
			});
		for (int i = 0; i < table->getRowCount(); i++)
		{
			table->fillRow(QList<QString> { QString::number(users[i]->getId()), users[i]->getName(), users[i]->getSurname(), users[i]->getFamily(), users[i]->getPhoneNumber(), users[i]->getEmail() }, i);
		}
		
	}
	if (isFamilySort) {
		std::sort(users.begin(), users.end(), [this](User* a, User* b) {
			if (isAscendingSort) {
				return a->getFamily() < b->getFamily();
			}
			else
			{
				return a->getFamily() > b->getFamily();
			}
			});
		for (int i = 0; i < table->getRowCount(); i++)
		{
			table->fillRow(QList<QString> { QString::number(users[i]->getId()), users[i]->getName(), users[i]->getSurname(), users[i]->getFamily(), users[i]->getPhoneNumber(), users[i]->getEmail() }, i);
		}
	
	}
	if (isNameSort) {
		std::sort(users.begin(), users.end(), [this](User* a, User* b) {
			if (isAscendingSort) {
				return a->getName() < b->getName();
			}
			else
			{
				return a->getName() > b->getName();
			}
			});
		for (int i = 0; i < table->getRowCount(); i++)
		{
			table->fillRow(QList<QString> { QString::number(users[i]->getId()), users[i]->getName(), users[i]->getSurname(), users[i]->getFamily(), users[i]->getPhoneNumber(), users[i]->getEmail() }, i);
		}

	}
	if (isPhoneNumberSort) {
		std::sort(users.begin(), users.end(), [this](User* a, User* b) {
			if (isAscendingSort) {
				return a->getPhoneNumber() < b->getPhoneNumber();
			}
			else
			{
				return a->getPhoneNumber() > b->getPhoneNumber();
			}
			});
		for (int i = 0; i < table->getRowCount(); i++)
		{
			table->fillRow(QList<QString> { QString::number(users[i]->getId()), users[i]->getName(), users[i]->getSurname(), users[i]->getFamily(), users[i]->getPhoneNumber(), users[i]->getEmail() }, i);
		}
	}
	if (isSurnameSort) {
		std::sort(users.begin(), users.end(), [this](User* a, User* b) {
			if (isAscendingSort) {
				return a->getSurname() < b->getSurname();
			}
			else
			{
				return a->getSurname() > b->getSurname();
			}
			});
		for (int i = 0; i < table->getRowCount(); i++)
		{
			table->fillRow(QList<QString> { QString::number(users[i]->getId()), users[i]->getName(), users[i]->getSurname(), users[i]->getFamily(), users[i]->getPhoneNumber(), users[i]->getEmail() }, i);
		}
	}
	if (isEmailSort) {
		std::sort(users.begin(), users.end(), [this](User* a, User* b) {
			if (isAscendingSort) {
				return a->getEmail() < b->getEmail();
			}
			else
			{
				return a->getEmail() > b->getEmail();
			}
			});
		for (int i = 0; i < table->getRowCount(); i++)
		{
			table->fillRow(QList<QString> { QString::number(users[i]->getId()), users[i]->getName(), users[i]->getSurname(), users[i]->getFamily(), users[i]->getPhoneNumber(), users[i]->getEmail() }, i);
		}
	}
	table->render();



}
void QtExcel::onEmailRadioButtonToggled()
{
	isEmailSort = true;
	isFamilySort = false;
	isNameSort = false;
	isPhoneNumberSort = false;
	isSurnameSort = false;
	isIdsort = false;
}
void QtExcel::onFamilyRadioButtonToggled()
{
	isEmailSort = false;
	isFamilySort = true;
	isNameSort = false;
	isPhoneNumberSort = false;
	isSurnameSort = false;
	isIdsort = false;
}
void QtExcel::onNameRadioButtonToggled()
{
	isEmailSort = false;
	isFamilySort = false;
	isNameSort = true;
	isPhoneNumberSort = false;
	isSurnameSort = false;
	isIdsort = false;
}
void QtExcel::onPhoneNumberradioButtonToggled()
{
	isEmailSort = false;
	isFamilySort = false;
	isNameSort = false;
	isPhoneNumberSort = true;
	isSurnameSort = false;
	isIdsort = false;
}
void QtExcel::onSurnamesRadioButtonToggled()
{
	isEmailSort = false;
	isFamilySort = false;
	isNameSort = false;
	isPhoneNumberSort = false;
	isSurnameSort = true;
	isIdsort = false;
}
void QtExcel::onIdRadioButtonToggled()
{
	isEmailSort = false;
	isFamilySort = false;
	isNameSort = false;
	isPhoneNumberSort = false;
	isSurnameSort = false;
	isIdsort = true;
}
void QtExcel::editSearch_textChanged(const QString &text) {

	searchVall = text;

}
void QtExcel::on_DeleteDuplicates_clicked() {
	QMap<QString, bool> seen; // Хранит уникальные значения
	for (int i = 0; i < table->getRowCount(); i++) {
		for (int j = 0; j < table->getColumnCount(); j++) {
			QString cellValue = table->getCell(i, j); // Получаем значение ячейки

			// Если значение уже встречалось, удаляем (очищаем) ячейку
			if (seen.contains(cellValue)) {
				table->setCell(i, j, "Deleted"); // Очищаем дубликат
			}
			else {
				// Добавляем значение в "seen" как уникальное
				seen[cellValue] = true;
			}
		}
	}
}

void QtExcel::on_jsonOutput_clicked() {
	QJsonArray tableData; // JSON-массив для хранения строк таблицы

	// Проходим по всем строкам и столбцам таблицы
	for (int i = 0; i < table->getRowCount(); i++) {
		QJsonObject rowObject; // JSON-объект для текущей строки
		for (int j = 0; j < table->getColumnCount(); j++) {
			QString cellValue = table->getCell(i, j); // Значение ячейки
			rowObject[QString::number(j)] = cellValue; // Добавляем пару "ключ-значение"
		}
		tableData.append(rowObject); // Добавляем строку в JSON-массив
	}

	// Создаём JSON-документ
	QJsonDocument jsonDocument(tableData);

	// Открываем диалог выбора файла для сохранения
	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Save JSON File"),
		QDir::homePath() + "/tableData.json",
		tr("JSON Files (*.json);;All Files (*)"));
	if (fileName.isEmpty()) {
		qWarning() << "File save operation canceled.";
		return; // Прерываем, если пользователь отменил выбор
	}

	// Сохраняем JSON в файл
	QFile jsonFile(fileName);
	if (jsonFile.open(QFile::WriteOnly)) {
		jsonFile.write(jsonDocument.toJson(QJsonDocument::Indented));
		jsonFile.close();
		qDebug() << "JSON saved to" << fileName;
	}
	else {
		qWarning() << "Could not open file for writing:" << fileName;
	}
}






void QtExcel::on_jsonInput_clicked() {
	// Открываем диалог выбора файла для загрузки
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open JSON File"),
		QDir::homePath(),
		tr("JSON Files (*.json);;All Files (*)"));
	if (fileName.isEmpty()) {
		qWarning() << "File open operation canceled.";
		return; // Прерываем, если пользователь отменил выбор
	}

	// Читаем JSON из файла
	QFile jsonFile(fileName);
	if (!jsonFile.open(QFile::ReadOnly)) {
		qWarning() << "Could not open file for reading:" << fileName;
		return;
	}

	QByteArray jsonData = jsonFile.readAll();
	jsonFile.close();

	// Парсим JSON-документ
	QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);
	if (jsonDocument.isNull() || !jsonDocument.isArray()) {
		qWarning() << "Invalid JSON format in file:" << fileName;
		return;
	}

	QJsonArray tableData = jsonDocument.array();

	// Устанавливаем размер таблицы
	int rowCount = tableData.size();
	int columnCount = tableData.isEmpty() ? 0 : tableData[0].toObject().size();
	table->setTableSize(rowCount, columnCount);
	table->render();

	// Заполняем таблицу данными из JSON
	for (int i = 0; i < rowCount; i++) {
		QJsonObject rowObject = tableData[i].toObject();
		for (int j = 0; j < columnCount; j++) {
			QString cellValue = rowObject[QString::number(j)].toString();
			table->setCell(i, j, cellValue);
		}
	}

	
	qDebug() << "JSON loaded from" << fileName;

}









