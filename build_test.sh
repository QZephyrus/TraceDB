#!/bin/bash

g++ DataBase.cpp DBTraceAPI.cpp test.cpp -otest -lboost_date_time `mysql_config --cflags --libs`