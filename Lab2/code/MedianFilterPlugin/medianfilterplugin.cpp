#include "medianfilterplugin.h"

QString MedianFilterPlugin::name()
{
    return "Median Filter";
}

inline void Sort(int & a, int & b)
{
    int t = a;
    a = std::min(t, b);
    b = std::max(t, b);
}

inline void bublle_sort(std::vector<int> &a){
    Sort(a[1], a[2]); Sort(a[4], a[5]); Sort(a[7], a[8]);
    Sort(a[0], a[1]); Sort(a[3], a[4]); Sort(a[6], a[7]);
    Sort(a[1], a[2]); Sort(a[4], a[5]); Sort(a[7], a[8]);
    Sort(a[0], a[3]); Sort(a[5], a[8]); Sort(a[4], a[7]);
    Sort(a[3], a[6]); Sort(a[1], a[4]); Sort(a[2], a[5]);
    Sort(a[4], a[7]); Sort(a[4], a[2]); Sort(a[6], a[4]);
    Sort(a[4], a[2]);
}

void MedianFilterPlugin::edit(const cv::Mat &input, cv::Mat &output)
{
    cv::Mat mat;
    cv::copyMakeBorder(input, mat, 1, 1, 1, 1, cv::BORDER_REPLICATE);

    for(int row = 1; row < mat.rows-1;row++)
    {
        for(int col = 1; col <  mat.cols-1; col++)
        {
            std::vector<int> R;
            std::vector<int> G;
            std::vector<int> B;
            for(int r = row-1;r <= row+1;r++)
            {
                for(int c = col-1;c <= col+1;c++)
                {
                    B.push_back(mat.at<cv::Vec3b>(r, c)[0]);
                    G.push_back(mat.at<cv::Vec3b>(r, c)[1]);
                    R.push_back(mat.at<cv::Vec3b>(r, c)[2]);
                }
            }
            bublle_sort(B);
            bublle_sort(G);
            bublle_sort(R);
            mat.at<cv::Vec3b>(row, col)[0] = B[4];
            mat.at<cv::Vec3b>(row, col)[1] = G[4];
            mat.at<cv::Vec3b>(row, col)[2] = R[4];
        }
    }

    cv::Rect result(1, 1, input.cols, input.rows);
    output = mat(result);
}
