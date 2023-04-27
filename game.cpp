#include "game.h"
#include "ui_game.h"

Game::Game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Game), m_timer(nullptr), ts_counter(0)
{
    ui->setupUi(this);

    // Set first team to Current team placeholder
    QFile file("team_names.txt");
    if(file.open(QIODevice::ReadOnly)){
        QString data;
        QTextStream out(&file);
        while (!out.atEnd()){
            data = out.readLine();
            teams.push_back(data);
            team_score[data] = 0;
        }
        file.close();
    }
    ui->curr_team->setText(teams[ts_counter]);

    // Create the countdown label
    m_countdownLabel = new QLabel(this);
    m_countdownLabel->setMinimumSize(80, 10);
    m_countdownLabel->move(20, 20);
    m_countdownLabel->setText("Time");

    // Create the timer and connect the timeout() signal to the onTimerTick() slot
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Game::onTimerTick);

//     Create the timer and connect the timeout() signal to the check_for_extra() slot to add extra words
    m_extra_timer = new QTimer(this);
    connect(m_extra_timer, &QTimer::timeout, this, &Game::check_for_extra);

    // disable Add Score To Team button
    ui->add_score->setEnabled(false);

    // Disable checkboxes
    ui->checkBox_1->setEnabled(false);
    ui->checkBox_2->setEnabled(false);
    ui->checkBox_3->setEnabled(false);
    ui->checkBox_4->setEnabled(false);
    ui->checkBox_5->setEnabled(false);
}

Game::~Game()
{
    delete ui;
}

void Game::onTimerTick()
{
    //Get from file round duration and add that as timer parameter (countdwon)
    QFile file_duration("dur_score.txt");
    QString data_time;
    if(file_duration.open(QIODevice::ReadOnly)){
        QTextStream out(&file_duration);
        data_time = out.readLine();
        file_duration.close();
    }
    static int remainingTime = data_time.toInt(); // seconds countdown

    if (remainingTime >= 0) {
        m_countdownLabel->setText(QString::number(remainingTime));
        remainingTime--;
    } else {
        m_timer->stop(); // Stop the timer when countdown is done
        m_countdownLabel->setText("Time's up!");
        remainingTime = data_time.toInt();
        ui->add_score->setEnabled(true);
        ui->add_score->show();
    }
}

void Game::check_for_extra()
{
    int cur_count = 0;
    is_not_extra = true;
    if (ui->checkBox_1->isChecked())
        cur_count++;
    if (ui->checkBox_2->isChecked())
        cur_count++;
    if (ui->checkBox_3->isChecked())
        cur_count++;
    if (ui->checkBox_4->isChecked())
        cur_count++;
    if (ui->checkBox_5->isChecked())
        cur_count++;
    if (cur_count % 5 == 0 && cur_count > 0)
    {
        filling_words();
        curr_count += cur_count;
        cur_count = 0;

        //Set checkboxes unchecked
        ui->checkBox_1->setChecked(false);
        ui->checkBox_2->setChecked(false);
        ui->checkBox_3->setChecked(false);
        ui->checkBox_4->setChecked(false);
        ui->checkBox_5->setChecked(false);

        is_not_extra = false;
    }
}

void Game::filling_words()
{
    // Read random words
    int random1 = 0;
    int random2 = 0;
    int random3 = 0;
    int random4 = 0;
    int random5 = 0;
    int num_lines = 0;
    int total_lines = 0;
    QFile file("words.txt");
    if(file.open(QIODevice::ReadOnly)){
        QString data;
        QTextStream out(&file);
        while (!out.atEnd()){
            data = out.readLine();
            total_lines++;
        }
        file.close();
    }
    if(file.open(QIODevice::ReadOnly)){
        QString data;
        QTextStream out(&file);
        srand(time(nullptr));
        random1 = rand() % total_lines;
        random2 = rand() % total_lines;
        random3 = rand() % total_lines;
        random4 = rand() % total_lines;
        random5 = rand() % total_lines;
        std::vector<QString> vec;
        while (!out.atEnd()){
            data = out.readLine();
            ++num_lines;
            if(num_lines == random1 || num_lines == random2 || num_lines == random3 || num_lines == random4 || num_lines == random5)
                vec.push_back(data);
        }
        file.close();

        //add random words to checkboxes
        ui->checkBox_1->setText(vec[0]);
        ui->checkBox_2->setText(vec[1]);
        ui->checkBox_3->setText(vec[2]);
        ui->checkBox_4->setText(vec[3]);
        ui->checkBox_5->setText(vec[4]);        
    }
}

void Game::on_pushButton_clicked()
{
    // Start the timer
    m_timer->start(1000);// 1000 ms = 1 second

    curr_count = 0;
    is_not_extra = true;
    filling_words();
    ui->pushButton->hide();
    ui->add_score->hide();

    // Enable checkboxes
    ui->checkBox_1->setEnabled(true);
    ui->checkBox_2->setEnabled(true);
    ui->checkBox_3->setEnabled(true);
    ui->checkBox_4->setEnabled(true);
    ui->checkBox_5->setEnabled(true);

    m_extra_timer->start(1000);
}

void Game::on_add_score_clicked()
{
    int cur_count = 0;
    // check if extra time doesnt exist
    if (is_not_extra == true)
    {
        if (ui->checkBox_1->isChecked())
            cur_count++;
        if (ui->checkBox_2->isChecked())
            cur_count++;
        if (ui->checkBox_3->isChecked())
            cur_count++;
        if (ui->checkBox_4->isChecked())
            cur_count++;
        if (ui->checkBox_5->isChecked())
            cur_count++;

        curr_count += cur_count;
    }
    // add points to team
    QString team = ui->curr_team->text();
    team_score[team] += curr_count;

    // change name of current team (placeholder)
    if (ts_counter == teams.size() - 1)
        ts_counter = 0;
    else
        ts_counter++;
    ui->curr_team->setText(teams[ts_counter]);

    // create window for scores
    score_window = new QWidget(this);
    score_window->setFixedSize(400, 300);
    score_window->setWindowTitle("SCORE");
    QVBoxLayout *layout = new QVBoxLayout(score_window);
    for (const auto& el : team_score){
        QLabel *team_name = new QLabel;
        team_name->setText(el.first + " -> " + QString::number(el.second));
        layout->addWidget(team_name);
    }
    QPushButton *ok_but = new QPushButton(score_window);
    ok_but->setText("OK");
    ok_but->setCursor(Qt::PointingHandCursor);
    ok_but->show();
    layout->addWidget(ok_but);
    connect(ok_but, SIGNAL(clicked()), this, SLOT(on_ok_clicked()));
    score_window->show();

    //Set checkboxes unchecked
    ui->checkBox_1->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
    ui->checkBox_5->setChecked(false);

    //Set default words in checkboxes
    ui->checkBox_1->setText("Word");
    ui->checkBox_2->setText("Word");
    ui->checkBox_3->setText("Word");
    ui->checkBox_4->setText("Word");
    ui->checkBox_5->setText("Word");

    // Disable checkboxes
    ui->checkBox_1->setEnabled(false);
    ui->checkBox_2->setEnabled(false);
    ui->checkBox_3->setEnabled(false);
    ui->checkBox_4->setEnabled(false);
    ui->checkBox_5->setEnabled(false);

    //Set default phrase for start
    m_countdownLabel->setText("Time");

    // show and hide buttons (Start Round and Add points to team)
    ui->pushButton->show();
    ui->add_score->hide();
}

void Game::on_ok_clicked()
{
    bool flag_of_win = true;
    // check if any team achieved to win score
    int win_count;
    QFile file("dur_score.txt");
    if(file.open(QIODevice::ReadOnly)){
        QString data;
        QTextStream out(&file);
        while (!out.atEnd()){
            data = out.readLine();
        }
        win_count = data.toInt();
        file.close();
    }
    for(const auto& el : team_score)
    {
        if (el.second >= win_count){
            QMessageBox::information(this, "CONGRATULATIONS", QString(" The team %1 is WINNER! ").arg(el.first));
            flag_of_win = false;
            delete m_timer;
            delete m_extra_timer;
            delete m_countdownLabel;
            delete score_window;

            hide();
            Play window;
            window.setModal(true);
            window.exec();
        }
    }
    if (flag_of_win)
        score_window->hide();
}

