//
// Created by xOx on 2023/4/18.
//

#ifndef TESTME_MMAP_H
#define TESTME_MMAP_H



#include <strings.h>
#include <unordered_map>
#include <functional>

using namespace std;

#define WALK_UnorderedMap(MAP)  \
		for(auto iter = (MAP).getMap()->begin(); iter != (MAP).getMap()->end(); iter++)

#define WALK_UnorderedMapFun(MAP, FUN)  \
		{unordered_map<K, V>* map_t1 = (MAP).getMap();\
		for(auto iter = map_t1->begin(); iter != map_t1->end(); iter++) FUN }

template <typename K, typename V>
class UnorderedMap
{
public:

    typedef unordered_map<K, V> _table;
//typedef bool (*EACH_FUN)(K & key, V & item);
    typedef std::function<bool(const K &, V &)> EACH_FUN;

    explicit UnorderedMap(int n=32):mMap(n)
    {
    }

    virtual ~UnorderedMap()
    {
        mMap.clear();
    }

    virtual bool hasItem(const K & k)
    {
        return mMap.find(k) != mMap.end();
    }

    /**
    * 查询结果放到 *v 中，并返回true
    * 如果没有查到，则返回 false
    */
    virtual bool getItem(const K & k, V * v)
    {
        auto iter = mMap.find(k);
        if (iter != mMap.end()) {
            *v = iter->second;
            return true;
        }else{
            return false;
        }
    }

    virtual V* getItemPtr(const K & k)
    {
        auto iter = mMap.find(k);
        if (iter != mMap.end()) {
            return &(iter->second);
        }else{
            return nullptr;
        }
    }

    virtual V & getItemDefault(const K & k, const V & default_v)
    {
        auto iter = mMap.find(k);
        if (iter != mMap.end()) {
            return iter->second;
        }else{
            return (V &)default_v;
        }
    }

    virtual V & getOrNew(const K & k)
    {
        return mMap[k];
    }

    virtual V & operator[](const K & k)
    {
        return mMap[k];
    }

    virtual bool addItem(const K & k, const V & item)
    {
        bool ret = false;
        if ( mMap.find(k) == mMap.end() ) {
            mMap[k] = item;
            ret = true;
        }
        return ret;
    }

    virtual V setItemAndGetOld(const K & k, const V & item)
    {
//		V old;
//        auto iter = mMap.find(k);
//		if (iter != mMap.end()) {
//			old = iter->second;
//		}else{
//			bzero(&old, sizeof(old));
//		}
//
//		mMap[k] = item;

        auto & v = mMap[k];
        auto old = v;
        v = item;
        return old;
    }

    virtual void setItem(const K & k, const V & item)
    {
        mMap[k] = item;
    }

    virtual int remove(const K & k)
    {
        return mMap.erase(k);
    }

    virtual void each(EACH_FUN func)
    {
        if( NULL == func )
            return;

        for(auto iter = mMap.begin(); iter != mMap.end(); iter++){
            if( !func(iter->first, iter->second) ){
                break;
            }
        }
    }

    /**
     * delete 所有成员，释放内存
     */
    void deleteAll()
    {
        for(auto iter = mMap.begin(); iter != mMap.end(); iter++){
            delete iter->second;
        }
        mMap.clear();
    }

    virtual void clear()
    {
        mMap.clear();
    }

    virtual int size()
    {
        return mMap.size();
    }

    bool empty() const
    {
        return mMap.empty();
    }

    virtual inline _table* getMap()
    {
        return &mMap;
    }
protected:
    _table mMap;
};

#endif //TESTME_MMAP_H
