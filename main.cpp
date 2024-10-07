#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

namespace fs = std::filesystem;
using namespace cv;
using namespace std;

const string folderPath = "C:/Users/Kareem/Downloads/img"; // Your folder path
const double targetSizeMB = 10.0; // Target size in MB

void resizeImage(const string& imagePath, const string& outputImagePath) {
    Mat img = imread(imagePath, IMREAD_UNCHANGED);

    if (img.empty()) {
        cerr << "Failed to load image: " << imagePath << endl;
        return;
    }

    auto originalSize = fs::file_size(imagePath);
    cout << "Original size of " << imagePath << ": " << originalSize << " bytes" << endl;

    double targetSizeBytes = targetSizeMB * 1024 * 1024; // Convert target size to bytes
    double scaleFactor = 1.0;

    while (originalSize > targetSizeBytes) {
        if (originalSize / 2 > targetSizeBytes) {
            scaleFactor *= 0.9; // Reduce size by 10%
        } else {
            scaleFactor *= 0.95; // Reduce size by 5%
        }

        Mat resizedImg;
        resize(img, resizedImg, Size(), scaleFactor, scaleFactor);
        imwrite(outputImagePath, resizedImg);

        originalSize = fs::file_size(outputImagePath);
        cout << "Resized image size: " << originalSize << " bytes" << endl;
    }
}

int main() {
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
    vector<string> originalImages; // To keep track of original images

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        const auto& filePath = entry.path().string();
        string extension = entry.path().extension().string();

        if (entry.is_regular_file() && (extension == ".jpg" || extension == ".jpeg" || extension == ".png")) {
            auto fileSize = fs::file_size(entry);

            if (fileSize > targetSizeMB * 1024 * 1024) {
                // Create the new file path for the resized image
                string newFilePath = folderPath + "/(Resized)" + entry.path().stem().string() + extension;
                resizeImage(filePath, newFilePath);
                originalImages.push_back(filePath); // Add original image to the list
            }
        }
    }

    // Ask user if they want to delete the original images
    char choice;
    cout << "Do you want to delete the original images? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        for (const auto& originalImage : originalImages) {
            fs::remove(originalImage); // Delete only the original images
            cout << "Deleted original image: " << originalImage << endl;
        }
    } else {
        cout << "Original images were not deleted." << endl;
    }

    return 0;
}
