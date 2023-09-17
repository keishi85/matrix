// / 6 /12
// 説明：クラスMatrixでは、行列処理を行うことができる。
//コンストラクタの引数にサイズを入力し、Set, Add,Sub, Mult関数を
//を用いて和、差、積を求めることができる。
// 動作確認：Wandbox https://wandbox.org/
// コンパイラ：gcc 12.2.0, C++17, no Boost, -pedantic
// 発展：Sub関数は、数値か行列を引数に指定することで差を計算できる。
//Mult関数では、行列の席を求めることができる。
//また、行列のサイズの違いにより採算ができない場合、それを示す表示を出力している

#include <iostream>
#include <iomanip>

// 行列クラス
class Matrix {
    double **matrix;
    int c, r;
    
public:
    Matrix();
    Matrix(int C, int R);
    Matrix(int C, int R, double *V);
    Matrix(Matrix &otherMatrix);
    ~Matrix();
    void Set(int c, int r, double v);
    void Set(double *V);
    double Get(int c, int r);
    void Add(double value);
    void Add(Matrix& otherMatrix);
    void Sub(double value);
    void Sub(Matrix& otherMatix);
    void Mult(Matrix& otherMatrix);
    void Show();
};

Matrix::Matrix(int C, int R){
    c = C;
    r = R;

    //二次元配列と零行列の生成
    matrix = new double*[C];
    for(int i = 0; i < C; i++){
        matrix[i] = new double[R];
        for(int j = 0; j < R; j++){
            matrix[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(int C, int R, double *V){
    c = C;
    r = R;
    matrix = new double*[C];
    for(int i = 0; i < C; i++){
        matrix[i] = new double[R];
        for(int j = 0; j < R; j++){
            matrix[i][j] = *V;
            V++;
        }
    }
}

Matrix::Matrix(Matrix &otherMatrix){
    c = otherMatrix.c;
    r = otherMatrix.r;
    matrix = new double *[c];
    for(int i = 0; i < c; i++){
        matrix[i] = new double[r];
        for(int j = 0; j < r; j++){
            matrix[i][j] = otherMatrix.matrix[i][j];
        }
    } 
}

Matrix::~Matrix() {
    for(int i = 0; i < c; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void Matrix::Set(int c, int r, double v){
    if(((c > 0) && (this->c >= c)) && ((r > 0) && (this->r >= r))){
        matrix[c-1][r-1] = v;
    }
    else{
        std::cout << "引数が間違っています。" << std::endl;
    }
}

void Matrix::Set(double *v){
    for(int i = 0; i < c; i++){
        for(int j = 0; j < r; j++){
            matrix[i][j] = *v;
            v++;
        }
    }
}

double Matrix::Get(int c, int r){
    if(((c > 0) && (this->c >= c)) && ((r > 0) && (this->r >= r))){
        return matrix[c-1][r-1];
    }
    else{
        std::cout << "\n";
        std::cout << "引数が間違っています。" << std::endl;
        return -99;
    }
}

void Matrix::Add(double value){
    for(int i = 0; i < c; i++){
        for(int j = 0; j < r; j++){
            matrix[i][j] += value;
        }
    }
}

void Matrix::Add(Matrix& otherMatrix){
    if((this->c == otherMatrix.c) && (this->r == otherMatrix.r)){
        for(int i = 0; i < c; i++){
            for(int j = 0; j < r; j++){
                matrix[i][j] += otherMatrix.matrix[i][j];
            }
        }
    }
    else{
        std::cout << "行列のサイズが異なります." << std::endl;
    }
    
}

void Matrix::Sub(double value){
    for(int i = 0; i < c; i++){
        for(int j = 0; j < r; j++){
            matrix[i][j] -= value;
        }
    }
}

void Matrix::Sub(Matrix& otherMatrix){
    if((this->c == otherMatrix.c) && (this->r == otherMatrix.r)){
        for(int i = 0; i < c; i++){
            for(int j = 0; j < r; j++){
                matrix[i][j] -= otherMatrix.matrix[i][j];
            }
        }
    }
    else{
        std::cout << "行列のサイズが異なります。" << std::endl;
    }
    
}

void Matrix::Mult(Matrix& otherMatrix){
   int c1 = this->c;
   int r1 = this->r;
   int c2 = otherMatrix.c;
   int r2 = otherMatrix.r;

   //演算可能か確認
   if(r1 != c2){
    std::cout << "行列のサイズが異なるため演算不可能。" << std::endl;
   } 

  else{
     Matrix result(c1, r2);  //結果を格納する行列

    for(int i = 0; i < c1; i++){
        for(int j = 0; j < r2; j++){
            double sum = 0.0;
            for(int k = 0; k < c2; k++){
                sum += this->matrix[i][k] * otherMatrix.matrix[k][j];
            }
            result.matrix[i][j] = sum;
        }
    }
    result.Show();
    }
}

void Matrix::Show(){
    for(int i = 0; i < c; i++){
        std::cout << "|" ;
        for(int j = 0; j < r-1; j++){
            std::cout << std::fixed << std::setprecision(2);
            std::cout << matrix[i][j] << " ";
        }
        std::cout << matrix[i][r-1] << "|" << "\n";
    }
}





// メイン関数
// 行列クラスの動作検証を行う
int main()
{
	// 零行列コンストラクタと表示テスト
    Matrix mat1(2, 2);
    // std::cout << "mat1=\n";
    // mat1.Show();
	// // 単一要素代入テスト
    // mat1.Set(0, 0, 1.0);
    // mat1.Set(0, 1, 2.0);
    // mat1.Set(1, 0, 3.0);
    // mat1.Set(1, 1, 4.0);
    // std::cout << "mat1=\n";
    // mat1.Show();

    // 単一要素取得テスト
    //std::cout << "mat1(0,1)=" << mat1.Get(0,1) << "\n";

	// // 要素指定コンストラクタのテスト
	double vals[4] = {5.1, 6.2, 7.3, 8.4};
    Matrix mat2(2, 2, vals);
    // std::cout << "mat2=\n";
    // mat2.Show();

    // // 複製コンストラクタのテスト
    Matrix mat3(mat1);
    // std::cout << "mat3=\n";
    // mat3.Show();
    // // 行列にスカラー値加算テスト
    mat3.Add(0.5);
    // std::cout << "mat3=\n";
    // mat3.Show();
    // std::cout << "mat1=\n";
    // mat1.Show();	// mat3 複製元のmat1は変化無いことを確認

	// // 行列加算テスト
	mat3.Add(mat2);
    // std::cout << "mat3=\n";
    // mat3.Show();
    // std::cout << "mat2=\n";
    // mat2.Show();	// mat2は変化無いことを確認	

    //サイズの異なる行列の足し算
    double v[] = {2.0, 3.0, 4.0, 1.0, 4.0, 5.0, 2.0, 1.0, 6.0};
    Matrix mat4(3, 3, v);
    double v2[] = {3.0, 1.0, 2.0, 2.0, 4.0, 2.0, 1.0, 5.0, 2.0};
    Matrix my(3,3, v2);
    mat4.Show();
    my.Show();
    mat4.Mult(my);
    
    return 0;
}
