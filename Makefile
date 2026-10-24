all: EulersMethod OtherMethods # simple make builds both programs.

EulersMethod.o: EulersMethod.cpp
  g++ -O3 -c EulersMethod.cpp 

EulersMethod: EulersMethod.o
  g++ -O3 EulersMethod.o -o EulersMethod

OtherMethods.o: OtherMethods.cpp
  g++ -O3 -c OtherMethods.cpp

OtherMethods: OtherMethods.o
  g++ -O3 OtherMethods.o -o OtherMethods

clean:
  rm -f EulersMethod OtherMethods

