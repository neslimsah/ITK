/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit (ITK)
  Module:    itkSmartPointer.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


Copyright (c) 2000 National Library of Medicine
All rights reserved.

See COPYRIGHT.txt for copyright details.

=========================================================================*/
#ifndef ITK_SMART_POINTER_H
#define ITK_SMART_POINTER_H

/** 
 * itkSmartPointer implements reference counting by overloading
 * operator -> (and *) among others. This allows natural interface
 * to the class referred to by the pointer without having to invoke
 * special Register()/UnRegister() methods directly.
 *
 * To compile / test this class
 * Windows: cl itkSmartPointerTest.cxx; .\itkSmartPointerTest.exe
 * linux:   c++ itkSmartPointerTest.cxx ./a.out
 * other:   CCcompiler itkSmartPointerTest.cxx  ./a.out
 */

template <class T>
class itkSmartPointer 
{
public:
  /** 
   * Constructor 
   */
  itkSmartPointer () 
    {
    m_Pointer = 0;
    }

  /** 
   * Const constructor 
   */
  itkSmartPointer (const itkSmartPointer<T> &p)
    { 
    m_Pointer = p.m_Pointer; 
    this->Register(); 
    }
  
  /** 
   * Constructor to pointer p 
   */
  itkSmartPointer (T *p)
    { 
    m_Pointer = p; 
    this->Register(); 
    }                             

  /** 
   * Destructor 
   */
  ~itkSmartPointer ()
    {
    this->UnRegister();
    }

  /** 
   * Overload operator -> 
   */
  T *operator -> () const
    { 
    return m_Pointer; 
    }

  /** 
    * Return pointer to object.
    */
   operator T * () const 
     { 
     return m_Pointer; 
     }
  /** 
    * Return pointer to object.
    */
   operator T * ()  
     { 
     return m_Pointer; 
     }

  /** 
   * Access funtion to pointer 
   */
  T *GetPointer () const 
    { 
    // This returns the pointer.  
    return m_Pointer; 
    }
  
  /** 
   * Comparison of pointers. Less than comparison. 
   */
  bool operator < (const itkSmartPointer &r)
    { 
    return (void*)m_Pointer < (void*) r.m_Pointer; 
    }

  /** 
   * Comparison of pointers. Greater than comparison. 
   */
  bool operator > (const itkSmartPointer &r)
    { 
    return (void*)m_Pointer > (void*) r.m_Pointer; 
    }

  /** 
   * Comparison of pointers. Less than or equal to comparison. 
   */
  bool operator <= (const itkSmartPointer &r)
    { 
    return (void*)m_Pointer <= (void*) r.m_Pointer; 
    }

  /** 
   * Comparison of pointers. Greater than or equal to comparison. 
   */
  bool operator >= (const itkSmartPointer &r)
    { 
    return (void*)m_Pointer >= (void*) r.m_Pointer; 
    }

  /** 
   * Overload operator assignment. 
   */
  itkSmartPointer &operator = (const itkSmartPointer &r)
    { 
    return this->operator = (r.GetPointer()); 
    }
  
  /** 
   * Overload operator assignment. 
   */
  itkSmartPointer &operator = (T *r)
    {                                                              
    if (m_Pointer != r)
      {
      this->UnRegister();
      m_Pointer = r;
      this->Register();
      }
    return *this;
    }

  /** 
   * Function to print object pointed to 
   */
  T *Print (std::ostream& os) const 
    { 
    // This prints the object pointed to by the pointer  
    (*m_Pointer).Print(os);  
        return m_Pointer;
    } 

private:
  /* The pointer to the object referrred to by this smart pointer. */
  T* m_Pointer;

  void Register()
    { 
    if (m_Pointer)
      {
      m_Pointer->Register();
      }
    }
  
  void UnRegister()
    {
    if (m_Pointer)
      {
      m_Pointer->UnRegister();
      }
    }
  
  inline friend std::ostream& operator<< (std::ostream& os, itkSmartPointer p) 
    {
    p.Print(os); 
    return os;
    }
};

#endif
