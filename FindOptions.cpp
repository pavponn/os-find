//
// Created by Павел Пономарев on 2019-04-11.
//

#include "FindOptions.h"

size_t FindOptions::getInode() const {
    return mInode;
}

void FindOptions::setInode(size_t inode) {
    hasInode = true;
    FindOptions::mInode = inode;
}

size_t FindOptions::getSize() const {
    return mSize;

}

void FindOptions::setSize(size_t size) {
    hasSize = true;
    FindOptions::mSize = size;
}

size_t FindOptions::getLinks() const {
    return mLinks;
}

void FindOptions::setLinks(size_t links) {
    hasLinks = true;
    FindOptions::mLinks = links;
}

const std::string& FindOptions::getRootPath() const {
    return mRootPath;
}

void FindOptions::setRootPath(const std::string& rootPath) {
    FindOptions::mRootPath = rootPath;
}

const std::string& FindOptions::getName() const {
    return mName;
}

void FindOptions::setName(const std::string& name) {
    hasName = true;
    FindOptions::mName = name;
}

const std::string& FindOptions::getExecPath() const {
    return mExecPath;
}

void FindOptions::setExecPath(const std::string& execPath) {
    hasExecPath = true;
    FindOptions::mExecPath = execPath;
}

sizeType FindOptions::getSizeType() const {
    return mSizeType;
}

void FindOptions::setSizeType(sizeType sizeType) {
    FindOptions::mSizeType = sizeType;
}

bool FindOptions::ifHasName() const {
    return hasName;
}

bool FindOptions::ifHasExecPath() const {
    return hasExecPath;
}

bool FindOptions::ifHasInode() const {
    return hasInode;
}

bool FindOptions::ifHasSize() const {
    return hasSize;
}

bool FindOptions::ifHasLinks() const {
    return hasLinks;
}
