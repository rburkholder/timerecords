/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Start.h
 * Author: rpb
 *
 * Created on September 22, 2018, 3:45 PM
 */

#ifndef START_H
#define START_H

#include <Wt/WContainerWidget.h>

namespace page {

class Main: public Wt::WContainerWidget {
public:
  Main( );  // will probably need database connection here
  virtual ~Main( );
private:
  
  Wt::WPushButton *m_btnStart;
  Wt::WPushButton *m_btnStop;
  Wt::WText *m_textOut; 
  
  void HandleBtnStart();
  void HandleBtnStop();
};

} // namespace page

#endif /* START_H */

