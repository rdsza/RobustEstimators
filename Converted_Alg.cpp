#include <vector>
#include <cmath>
int main() {
    int cols = 64;
    int rows = 64;
    std::vector<std::vector<int>> countImage(rows, std::vector<int>(cols, 0));
    std::vector<std::vector<int>> meanImage(rows, std::vector<int>(cols, 0));
    std::vector<std::vector<int>> sumSquaredImage(rows, std::vector<int>(cols, 0));
    int threshold = 3;
    int buffer_size = 5;
    for (int i = 0; i < 5000; i++) {
        for (int j = 0; j < 64; j++){
            for (int k = 0; k < 64; k++){
                int n = countImage[j][k];    // Count of valid values
                int mean = meanImage[j][k];   // Running mean
                int M2 = sumSquaredImage[j][k];
                int value = volume[i][j][k];
                int variance;
                int stddev;
                
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
                int delta = value - mean;
                mean += delta / n;
                int delta2 = value - mean;
                M2 += delta * delta2;

                    
                    //Update Values
                countImage[j][k] = n;     // Count of valid values
                meanImage[j][k] = mean;  //Running mean
                sumSquaredImage[j][k] = M2;
            

   
            }
        }
    }




    return 0;
}

int** createArray(int rows, int cols) {
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }
    return matrix;
}
