#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

vector<vector<float>> imageAlg(vector<vector<vector<float>>> volume) {
    int cols = 64;
    int rows = 64;
    std::vector<std::vector<int>> countImage(rows, std::vector<int>(cols, 0));
    std::vector<std::vector<float>> meanImage(rows, std::vector<float>(cols, 0.0));
    std::vector<std::vector<float>> sumSquaredImage(rows, std::vector<float>(cols, 0.0));
    int threshold = 3;
    int buffer_size = 5;
    for (int i = 0; i < 5000; i++) {
        for (int j = 0; j < 64; j++){
            for (int k = 0; k < 64; k++){
                int n = countImage[j][k];    // Count of valid values
                float mean = meanImage[j][k];   // Running mean
                float M2 = sumSquaredImage[j][k];
                float value = volume[i][j][k];
                float variance;
                float stddev;
                
                if (n > buffer_size){     
                    // Calculate temporary standard deviation
                    if(n>1) 
                        variance = M2  / (n - 1);
                        
                    else 
                        variance = 0;
                    stddev = sqrt(variance);
                }
                    // Check if value is within threshold * stddev from the mean
                    if (abs(value - mean) > threshold * stddev)
                        //print(f"Value {value} is considered an outlier and will be skipped.")
                        continue;

                // Update running statistics for non-outliers
                n += 1;
                float delta = value - mean;
                mean += delta / n;
                float delta2 = value - mean;
                M2 += delta * delta2;

                    
                    //Update Values
                countImage[j][k] = n;     // Count of valid values
                meanImage[j][k] = mean;  //Running mean
                sumSquaredImage[j][k] = M2;
            

   
            }
        }
    }
    return meanImage;
}


int main(){
    float percentMeanErrors[64][64];
    vector<vector<vector<float>>> volume = getVolume();
    vector<vector<float>> trueMeans = getTrueMeans();
    vector<vector<float>> meanImage  = imageAlg(volume);
    for (int j = 0; j<64; j++){
        for (int k = 0; k<64; k++){
            percentMeanErrors[j][k] = (trueMeans[j][k] - meanImage[j][k])/trueMeans[j][k] * 100;
        }
    }
    int sum = 0;
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++) {
            sum += percentMeanErrors[i][j];
        }
    }
    double mean = static_cast<double>(sum) / (4096);

    cout << "Mean of the 2D array: " << mean << endl;


    return 0;
}




vector<vector<float>> getTrueMeans(){

     std::ifstream file("trueMeans.txt"); // Replace "data.txt" with your file name
    int rows, cols;

    // Read the dimensions of the array
    file >> rows >> cols;

    // Create a 2D vector to store the array
    std::vector<std::vector<float>> array(rows, std::vector<float>(cols));

    // Read the data from the file into the array
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> array[i][j];
        }
    }
    return array;
}

 vector<vector<vector<float>>> getVolume(){
    int x, y, z;
    ifstream file("data.txt");

    // Read dimensions
    file >> x >> y >> z;

    // Create 3D vector
    vector<vector<vector<float>>> array3D(x, vector<vector<float>>(y, vector<float>(z)));

    // Load data
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            for (int k = 0; k < z; ++k) {
                file >> array3D[i][j][k];
            }
        }
    }

    file.close();

    return array3D;


 }


