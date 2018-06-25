###README

#Input data structure csv file comma separated:

Example Data can be found in sampleData/input.csv in format:

|id|executionTime|
|:---| :----|
|1 |2|
|1 |2.0|

#Output
As a output program return std::vector<float> with estimated time-outs. Size of vector is dependend on maxId from input data.
Example output: 24.3


#Design

![alt text](https://image.ibb.co/d4qnvT/Przechwytywanie.png)

#Algorithm
1. Input data is separated for segregated vector of execution times for specific ids.
2. That segregater data is sorted and program cut out 10% of test from begin and from end. That removes extremum values.
![alt text](https://image.ibb.co/gQq0kT/plot.png)
3. For remaining values averange is calculated. Return value of evaluation described is in equation: 



Evaluation = (1.0f + averange) * (1 + additionPercent)

where +1 addition is prevention for small historical datasets, and (1 + additionPercent) is error margin.

Evaluation can be different for example instead of average, mediana can be used.
It can be also extended by CI overload or any other parameter to be more precise.

Evaluation should be customized to data sets where test execution times are very high or very low
e.g. below 1s or near that value.




