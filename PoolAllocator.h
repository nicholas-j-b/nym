#include <memory>

namespace mem{
  enum LINE_MODE {math, set, non};
  enum ERROR_CODE {noError, unknownError};

  union Content {
    long lNums[cfg::CONTENT_SIZE];
    double dNums[cfg::CONTENT_SIZE];
    char cChar[cfg::CONTENT_SIZE * sizeof(long)];
  };

  class NumVector{
  protected:
    Content m_content;
  public:
    NumVector() {};
    ~NumVector() {};
    NumVector(const NumVector& other) = delete;
    NumVector(const NumVector&& other) = delete;
    NumVector& operator=(const NumVector& other) = delete;
    NumVector& operator=(const NumVector&& other) = delete;

    void set_all(int a){
      for (size_t i = 0; i < cfg::CONTENT_SIZE; ++i){
        m_content.lNums[i] = a;
      }
    }

    void print(size_t a){
      for(size_t i = 0; i < a; ++i){
        std::cout<<m_content.lNums[i]<<", ";
      }
    }
  };

  class lNumVector : public NumVector {
  private:
  public:
    long operator[](int i) const {return m_content.lNums[i];}
    long& operator[](int i){if(i <= cfg::CONTENT_SIZE){return m_content.lNums[i];}}

    void zeros(){
      std::memset(m_content.lNums, 0, cfg::CONTENT_SIZE);
    }
  };

  class dNumVector : public NumVector {
  private:
  public:
    double operator[](int i) const {return m_content.dNums[i];}
    double& operator[](int i){if(i <= cfg::CONTENT_SIZE){return m_content.dNums[i];}}
  };

  template <typename T>
  union PoolChunk {
    T value;
    PoolChunk<T>* nextPoolChunk;

    PoolChunk() {};
    ~PoolChunk() {};
  };

  template <typename T>
  class PoolAllocator{
  private:
    size_t m_size = 0;

    PoolChunk<T>* m_data = nullptr;
    PoolChunk<T>* m_head = nullptr;
  public:
    explicit PoolAllocator(size_t size = cfg::NUM_CONTENT_IN_POOL)
      : m_size(size)
    {
      m_data = new PoolChunk<T>[size];
      m_head = m_data;

      for(size_t i = 0; i < m_size -1; i++){
        m_data[i].nextPoolChunk = std::addressof(m_data[i + 1]);
      }
      m_data[m_size - 1].nextPoolChunk = nullptr;
    }
    ~PoolAllocator(){
      delete[] m_data;
      m_data = nullptr;
      m_head = nullptr;
    }
    PoolAllocator(const PoolAllocator& other) = delete;
    PoolAllocator(const PoolAllocator&& other) = delete;
    PoolAllocator& operator=(const PoolAllocator& other) = delete;
    PoolAllocator& operator=(const PoolAllocator&& other) = delete;

    template <typename... arguments>
    T* allocate(arguments&&... args){
      if(m_head == nullptr){
        return nullptr;
      }
      PoolChunk<T>* poolChunk = m_head;
      m_head = m_head->nextPoolChunk;
      T* retVal = new (std::addressof(poolChunk->value)) T (std::forward<arguments>(args)...);
      return retVal;
    }

    void deallocate(T* data){
      data->~T();
      PoolChunk<T>* poolChunk = reinterpret_cast<PoolChunk<T>*>(data);
      poolChunk->nextPoolChunk = m_head;
      m_head = poolChunk;
    }
  };
}
