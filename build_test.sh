#!/bin/bash

g++ DataBase.cpp DataTraceAPI.cpp test.cpp -otest -lboost_date_time `mysql_config --cflags --libs`