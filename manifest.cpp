// C++17: สแกนโฟลเดอร์ assets แล้วสร้าง assets/manifest.json ให้หน้าสื่อใช้
// คอมไพล์: g++ -std=c++17 tools/manifest.cpp -o tools/manifest && ./tools/manifest
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
namespace fs = std::filesystem;

static std::string category(const std::string& n) {
    if (n.rfind("photo-", 0) == 0) return "photo";
    if (n.rfind("poster-", 0) == 0 || n.rfind("bg-", 0) == 0) return "poster";
    if (n.rfind("logo-", 0) == 0) return "logo";
    return "other";
}

int main() {
    std::vector<fs::path> files;
    for (auto& e : fs::directory_iterator("assets")) {
        auto ext = e.path().extension().string();
        if (ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".webp") files.push_back(e.path());
    }
    std::sort(files.begin(), files.end());
    std::ofstream out("assets/manifest.json");
    out << "[\n";
    for (size_t i = 0; i < files.size(); ++i) {
        auto name = files[i].filename().string();
        out << "  {\"file\":\"assets/" << name << "\",\"type\":\"" << category(name)
            << "\",\"bytes\":" << fs::file_size(files[i]) << "}" << (i + 1 < files.size() ? "," : "") << "\n";
    }
    out << "]\n";
    std::cout << "manifest.json: " << files.size() << " files\n";
}
