// Main window for the Network Animation Viewer
// George F. Riley, Georgia Tech, Spring 2009

#ifndef __ANIM_VIEW_H__
#define __ANIM_VIEW_H__
#include <vector>
#include <deque>

#include <QWidget>
#include <QMainWindow>
class QPaintEvent;
class QResizeEvent;
class QScrollArea;
class QTimer;
class QLabel;
class QSlider;

#include "NetModel.h"

#define MAX_SLIDER 21

typedef std::pair<Time_t, NetModel> HistoryPair_t;
typedef std::deque<HistoryPair_t>   HistoryDeq_t;

class NetView : public QWidget
{
  Q_OBJECT
public:
  NetView(NetModel*, QWidget*);
  void SetUpdateInterval(Time_t, bool = true);
  void StartAnimation(bool);
  void SetViewSize(int w, int h);
  NetModel* GetNetModel();
  void UpdateSimTime(Time_t);
  //void SetUpdateRate(int);
  void AddHistory(Time_t, NetModel*);  // Add the current pixmap to the history
  //Inherited from QWidget
  void paintEvent(QPaintEvent*);
  void resizeEvent(QResizeEvent*);
  void update();
private:
  QPointF      ToPixels(QPointF); // Network location to screen location
public:
  int w;                    // Current width
  int h;                    // Current height
  int minW;                 // Minimum width
  int minH;                 // Minimum height
  QPixmap*     paintPM;     // The pixmap to paint
  int          historyIndex;// If >= 0, display from history
  NetModel*    m;           // The corresponding model
  QWidget*     mainWidget;  // Used in saving the png files for movies
  QScrollArea* sa;     
  QTimer*      timer;
  QTimer*      recordTimer;
  QLabel*      simTimeWidget;
  QLabel*      updateRate;
  QSlider*     backupSlider;
  QSlider*     updateRateSlider;
  Time_t       updateInterval;
  // The history buffer allows backing up. This is a memory hog, so the
  // limit insures we don't have too many of them
  unsigned     maxHistorySize;
  QRectF       viewRect;
  int          nodeRadius; // in pixels
  int          linkWidth;  // in pixels
  bool         paused;
  int          framesPerSecond;  // For movie logging
private:
  HistoryDeq_t  history;
  double        updateRates[MAX_SLIDER];
public:
  // Static methods
  static NetView* Create(QApplication*); // Creates the view windows
public slots:
  void TimeToUpdate();
  void TimeToRecord();
  void Play();
  void Pause();
  void Record();
  void BackupSliderMoved(int);
  void RateSliderMoved(int);
};
#endif
