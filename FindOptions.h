//
// Created by Павел Пономарев on 2019-04-11.
//

#pragma once

#include <string>

enum sizeType { MORE, LESS, EXACT };

class FindOptions {
public:
    FindOptions() = default;

    size_t getInode() const;
    void setInode(size_t inode);

    size_t getSize() const;
    void setSize(size_t size);

    size_t getLinks() const;
    void setLinks(size_t links);

    const std::string& getRootPath() const;
    void setRootPath(const std::string& rootPath);

    const std::string& getName() const;
    void setName(const std::string& name);

    const std::string& getExecPath() const;
    void setExecPath(const std::string& execPath);

    sizeType getSizeType() const;
    void setSizeType(sizeType sizeType);

    bool ifHasName() const;
    bool ifHasExecPath() const;
    bool ifHasInode() const;
    bool ifHasSize() const;
    bool ifHasLinks() const;

private:
    std::string mRootPath;
    std::string mName;
    std::string mExecPath;
    size_t mInode;
    size_t mSize;
    size_t mLinks;
    sizeType mSizeType;
    bool hasName = false, hasExecPath = false,
    hasInode = false, hasSize = false, hasLinks = false;
};

