#include "../generator.cc"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace ailab;

generator_t build_mock_generator()
{
    std::string line;
    size_t reader;
    vector<size_t> topics;

    config_t config;
    ifstream config_file("inputs/config.txt");
    if (config_file.is_open())
    {

        config_file >> reader;
        config.variants_count = reader;

        config_file >> reader;
        config.questions_count = reader;

        while (getline(config_file, line))
        {
            if (line != "")
            {
                try
                {
                    reader = stoi(line);
                    topics.push_back(reader);
                }
                catch (exception e)
                {
                    cout << "EXCEPTION AT LINE " + line + " AT CONFIG.TXT" << endl;
                }
            }
        }
        config.topics = topics;
    }
    config_file.close();

    vector<topic_t> tps;
    ifstream topics_file("inputs/topics.txt");
    if (topics_file.is_open())
    {
        while (getline(topics_file, line))
        {
            if (line != "")
            {
                try
                {
                    int parent;
                    string text = "";

                    reader = stoi(line);
                    topics_file >> parent;
                    while (text == "")
                    {
                        getline(topics_file, text);
                    }

                    topic_t t(reader, parent, text);
                    tps.push_back(t);
                }
                catch (exception e)
                {
                    cout << "EXCEPTION AT LINE " + line + " AT TOPICS.TXT" << endl;
                }
            }
        }
    }

    vector<question_t> questions;
    ifstream questions_file("inputs/questions.txt");
    if (questions_file.is_open())
    {
        while (getline(questions_file, line))
        {
            if (line != "")
            {
                try
                {
                    int topic_id, difficulty;
                    string text = "";

                    reader = stoi(line);
                    questions_file >> topic_id;
                    questions_file >> difficulty;
                    while (text == "")
                    {
                        getline(questions_file, text);
                    }

                    question_t q(reader, topic_id, difficulty, text);
                    questions.push_back(q);
                }
                catch (exception e)
                {
                    cout << "EXCEPTION AT LINE " + line + " AT TOPICS.TXT" << endl;
                }
            }
        }
    }
    generator_t g(config, tps, questions);
    return g;
}

int main()
{
    cout << "TESTS STARTED" << endl;
    generator_t g = build_mock_generator();
    variants_t v = g.generate();
    return 0;
}
