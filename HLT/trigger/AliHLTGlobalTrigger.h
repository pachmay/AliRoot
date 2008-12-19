#ifndef ALIHLTGLOBALTRIGGER_H
#define ALIHLTGLOBALTRIGGER_H
/* This file is property of and copyright by the ALICE HLT Project        *
 * ALICE Experiment at CERN, All rights reserved.                         *
 * See cxx source for full Copyright notice                               */

/// @file   AliHLTGlobalTrigger.h
/// @author Artur Szostak <artursz@iafrica.com>
/// @date   19 Dec 2008
/// @brief  Declaration of the AliHLTGlobalTrigger base class.

#include "TObject.h"
#include "TArrayL64.h"
#include "AliHLTDataTypes.h"
#include "AliHLTLogging.h"

class AliHLTTriggerDecision;
class AliHLTGlobalTriggerDecision;

/**
 * \class AliHLTGlobalTrigger
 * This class is an abstract class. Classes which derive from this class should
 * implement the logic for a particular trigger menu. The AliHLTTriggerMenu class
 * creates a class deriving from AliHLTGlobalTrigger on the fly to implement the
 * trigger logic for that particular trigger menu.
 */
class AliHLTGlobalTrigger
{
 public:
  
  /**
   * Default constructor.
   */
  AliHLTGlobalTrigger();
  
  /**
   * Default destructor.
   */
  virtual ~AliHLTGlobalTrigger();
  
  /**
   * Abstract method to indicate that a new event is being processed and the
   * internal buffers should be cleared or reset.
   */
  virtual void NewEvent() = 0;
  
  /**
   * Abstract method which should fill in the internal attributes from the given
   * trigger decision.
   * \param  decision  The trigger decision to fill from.
   */
  virtual void Add(const AliHLTTriggerDecision* decision) = 0;
  
  /**
   * Abstract method which should fill in the internal attributes from the given
   * object.
   * \param  object  The object to fill from.
   * \param  type  The data block type the object was found in.
   * \param  spec  The data block specification the object was found in.
   */
  virtual void Add(
      const TObject* object,
      const AliHLTComponentDataType& type,
      AliHLTUInt32_t spec
    ) = 0;
  
  /**
   * Abstract method that calculates the trigger decision
   * \returns The global HLT trigger decision result.
   */
  virtual AliHLTGlobalTriggerDecision* CalculateTriggerDecision() = 0;
  
  /**
   * Creates a new instance of a particular trigger class.
   * \param name  The name of the class to create.
   * \returns the new trigger class instance which needs to be deleted by the
   *    caller with the delete operator.
   */
  static AliHLTGlobalTrigger* CreateNew(const char* name) { return Factory::CreateNew(name); }
  
 protected:
  
  /**
   * The factory object is used to create new instances of classes via the
   * AliHLTGlobalTrigger::CreateNew method.
   * A single static instance of a factory must be created by classes deriving
   * from AliHLTGlobalTrigger so that AliHLTGlobalTrigger::CreateNew will work
   * properly.
   */
  class Factory : public AliHLTLogging
  {
   public:
    
    /**
     * Default constructor registers a class factory for the creation of new
     * instances of classes deriving from AliHLTGlobalTrigger.
     */
    Factory();
    
    /**
     * The default destructor deregisters the factory from the class factory list.
     */
    ~Factory();
    
    /**
     * Creates a new instance of a particular trigger class.
     * \param name  The name of the class to create.
     * \returns the new trigger class instance which needs to be deleted by the
     *    caller with the delete operator.
     */
    static AliHLTGlobalTrigger* CreateNew(const char* name);
    
    /**
     * Returns the class name of the object returned by the New() method.
     */
    virtual const char* ClassName() const = 0;
    
    /**
     * Creates and returns a new instance of a trigger class.
     * The returned object should be deleted via the delete operator.
     */
    virtual AliHLTGlobalTrigger* New() const = 0;
    
   private:
    
    enum {kMaxFactories = 8}; /// The maximum number of factories that can be registered.
    
    static Factory* fFactory[kMaxFactories];
  };
  
  /// Not implemented. Do not allow copying of this object.
  AliHLTGlobalTrigger(const AliHLTGlobalTrigger& obj);
  /// Not implemented. Do not allow copying of this object.
  AliHLTGlobalTrigger& operator = (const AliHLTGlobalTrigger& obj);
  
 private:
  
  TArrayL64 fCounters; //! Event trigger counters. One counter for each trigger class.
  
  ClassDef(AliHLTGlobalTrigger, 0) // Global HLT trigger base class which implements logic for a particular trigger menu.
};

#endif // ALIHLTGLOBALTRIGGER_H

