////////////////////////////////////////////////////////////////////////////////
//
// SpeciesHandler.h
//
////////////////////////////////////////////////////////////////////////////////
// $Id: SpeciesHandler.h,v 1.1 2003-05-16 16:14:00 fgygi Exp $

#ifndef SPECIESHANDLER_H
#define SPECIESHANDLER_H

#include "StructureHandler.h"

class Species;

class SpeciesHandler : public StructureHandler
{
  private:
  
  Species& sp_;
  int current_l, current_size;
  string current_name, current_href;
  double current_interval;
    
  public:
  
  // Start of an element handled by SpeciesHandler
  virtual void startElement(const XMLCh* const uri,const XMLCh* const localname,
      const XMLCh* const qname, const Attributes& attributes);

  // End of an element handled by SpeciesHandler
  virtual void endElement(const XMLCh* const uri, const XMLCh* const localname, 
      const XMLCh* const qname, string& content);
  
  // start a subHandler if possible
  virtual StructureHandler* startSubHandler(const XMLCh* const uri,
    const XMLCh* const localname, const XMLCh* const qname, 
    const Attributes& attributes);
    
  // end subHandler
  virtual void endSubHandler(const XMLCh* const uri,
    const XMLCh* const localname, const XMLCh* const qname, 
    const StructureHandler* const subHandler);

  SpeciesHandler(Species& sp);
  ~SpeciesHandler();
};
#endif