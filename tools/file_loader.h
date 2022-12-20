#pragma once

#include <QFile>
#include <QHash>
#include <QJsonDocument>
#include <QPixmap>
#include <QString>

#include <variant>

class FileLoader {
 public:
  FileLoader() = delete;
  static std::variant<QJsonDocument,
                      QPixmap> GetFile(const QString& file_name);

 private:
  static bool IsJsonFile(const QString& file_name);
  static bool IsImageFile(const QString& file_name);

  static QJsonDocument& GetJsonFile(const QString& file_name);
  static QPixmap& GetImageFile(const QString& file_name);
  static QString CastFileToString(const QString& file_name);

  static bool endsWith(const QString& filename, const QString& suffix) {
    return filename.endsWith(suffix);
  }

  template<typename... Args>
  static bool endsWith(const QString& filename,
                       const QString& suffix,
                       const Args& ... args) {
    return filename.endsWith(suffix) || endsWith(filename, args...);
  }

  static QHash<QString, QJsonDocument> container_json_;
  static QHash<QString, QPixmap> container_image_;
};
