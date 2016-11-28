 #include <QVBoxLayout>
 #include <QHBoxLayout>
 #include <QPushButton>
#include <QToolButton>
#include <QWidgetAction>
#include <QMenu>
#include <QPropertyAnimation>
#include <QFrame>

#include "acceptdenyfriendrequests.hpp"
#include "ui_acceptdenyfriendrequests.hpp"

 FriendRequestWidget::FriendRequestWidget(QWidget *parent) :
     QWidget(parent),
     it(requests)
 {
-    button = new QToolButton(this);
-    button->setPopupMode(QToolButton::InstantPopup);
-    button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
-
-    menu = new QMenu( this);
-    QWidgetAction *action = new QWidgetAction(this);
-    actionDefaultWidget = new QWidget(this);
-    QVBoxLayout *menulayout = new QVBoxLayout(actionDefaultWidget);
-    menulayout->setContentsMargins(2,2,2,2);
-    menulayout->setSpacing(2);
-    action->setDefaultWidget(actionDefaultWidget);
-    menu->addAction(action);
-
-    clientId = new ElideLabel(actionDefaultWidget);
+    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
+
+    button = new QPushButton(this);
+    button->setCheckable(true);
+    button->setProperty("class", "frqButton"); // for CSS styling
+
+    detailsWidget = new QFrame(this);
+    detailsWidget->setFrameShape(QFrame::StyledPanel);
+    detailsWidget->setProperty("class", "frqDetails"); // for CSS styling
+
+    clientId = new ElideLabel(detailsWidget);
     clientId->setTextElide(true);
     clientId->setTextElideMode(Qt::ElideRight);
+    clientId->setFixedWidth(100);

-    message = new QLabel(actionDefaultWidget);
+    message = new QLabel(detailsWidget);
     message->setWordWrap(true);

-    accaptButton = new QPushButton(actionDefaultWidget);
-    accaptButton->setIcon(QIcon("://icons/accept.png"));
+    acceptButton = new QPushButton(detailsWidget);
+    acceptButton->setIcon(QIcon("://icons/accept.png"));
+    acceptButton->setToolTip(tr("Accept request"));

-    rejectButton = new QPushButton(actionDefaultWidget);
+    rejectButton = new QPushButton(detailsWidget);
     rejectButton->setIcon(QIcon("://icons/cancel.png"));
+    rejectButton->setToolTip(tr("Reject request"));

-    connect(accaptButton, &QPushButton::clicked, this, &FriendRequestWidget::acceptUser);
-    connect(rejectButton, &QPushButton::clicked, this, &FriendRequestWidget::rejectUser);
+    nextButton = new QPushButton(detailsWidget);
+    nextButton->setIcon(QIcon("://icons/resultset_next.png"));
+    nextButton->setToolTip(tr("Next request"));

     QHBoxLayout *buttonLayout = new QHBoxLayout;
-    buttonLayout->addWidget(accaptButton);
+    buttonLayout->addWidget(acceptButton);
     buttonLayout->addWidget(rejectButton);
+    buttonLayout->addWidget(nextButton);
     buttonLayout->setContentsMargins(0,0,0,0);

-    menulayout->addWidget(clientId);
-    menulayout->addWidget(message);
-    menulayout->addLayout(buttonLayout);
+    QVBoxLayout *detailsLayout = new QVBoxLayout(detailsWidget);
+    detailsLayout->setContentsMargins(0,0,0,0);
+    detailsLayout->setSpacing(2);
+    detailsLayout->addWidget(clientId);
+    detailsLayout->addWidget(message);
+    detailsLayout->addLayout(buttonLayout);

     QVBoxLayout *layout = new QVBoxLayout(this);
     layout->addWidget(button);
-    layout->setContentsMargins(0,0,0,0);
+    layout->addWidget(detailsWidget);
+    layout->setContentsMargins(2,2,2,2);
     layout->setSpacing(0);

+    connect(button,       &QPushButton::toggled, this, &FriendRequestWidget::showDetails);
+    connect(acceptButton, &QPushButton::clicked, this, &FriendRequestWidget::acceptUser);
+    connect(rejectButton, &QPushButton::clicked, this, &FriendRequestWidget::rejectUser);
+    connect(nextButton,   &QPushButton::clicked, this, &FriendRequestWidget::nextRequest);
+
+    animation = new QPropertyAnimation(detailsWidget, "maximumHeight");
+    animation->setDuration(200);
+    animation->setLoopCount(1);
+
+    if(Settings::getInstance().isAnimationEnabled()) {
+        detailsWidget->setMaximumHeight(0);
+    } else {
+        detailsWidget->hide();
+    }
+
     updateGui();
 }

 void FriendRequestWidget::addFriendRequest(const QString &userId, const QString &msg)
 {
     requests.insert(userId, msg);
+    goFirst();
+
     updateGui();
 }

 void FriendRequestWidget::resizeEvent(QResizeEvent *e)
 {
     QWidget::resizeEvent(e);
-    updateGui();
+    clientId->setMaximumWidth(width());
 }

 void FriendRequestWidget::acceptUser()
 {
     emit userAccepted(it.key());
     it.remove();
-    button->menu()->close();
+    goFirst();
+
     updateGui();
 }

 void FriendRequestWidget::rejectUser()
 {
     it.remove();
-    button->menu()->close();
+    goFirst();
+
+    updateGui();
+}
+
+void FriendRequestWidget::showDetails(bool show)
+{
+    if(show) {
+        goFirst();
+
+        detailsWidget->show();
+        if(Settings::getInstance().isAnimationEnabled()) {
+            animation->setKeyValueAt(0, 0);
+            animation->setKeyValueAt(1, detailsWidget->sizeHint().height());
+            animation->start();
+        } else {
+            detailsWidget->setMaximumHeight(detailsWidget->sizeHint().height());
+        }
+    }
+    else {
+        if(Settings::getInstance().isAnimationEnabled()) {
+            animation->setKeyValueAt(0, detailsWidget->sizeHint().height());
+            animation->setKeyValueAt(1, 0);
+            animation->start();
+        } else {
+            detailsWidget->hide();
+        }
+    }
+}
+
+void FriendRequestWidget::nextRequest()
+{
+    if(it.hasNext()) {
+        it.next();
+    } else {
+        goFirst();
+    }
     updateGui();
 }

 void FriendRequestWidget::updateGui()
 {
     button->setText(tr("%n friend request(s)","", requests.count()));
     if(requests.count() > 0) {
-        button->setMenu(menu);
-        button->setVisible(true);
-        it.toFront();
-        it.next();
-
+        setVisible(true);
         clientId->setText(tr("Client ID: %1").arg(it.key()));
         clientId->setToolTip(it.key());
-        message->setText(QString("\"<i>%1</i>\"").arg(it.value()));
+        message->setText(QString("<i>\"%1\"</i>").arg(it.value()));
+
+        // Hide next button
+        if(requests.count() == 1) {
+            nextButton->hide();
+        } else {
+            nextButton->show();
+        }
     }
     else {
-        button->setMenu(NULL);
-        button->setVisible(false);
+        button->setChecked(false);
+        setVisible(false);
         clientId->clear();
         message->clear();
     }
+}

-    // Recalculate popup size
-    if (button->menu()) {
-        button->menu()->setFixedWidth(button->width());
-        actionDefaultWidget->setFixedWidth(button->menu()->width() - 4);
-        actionDefaultWidget->setFixedHeight(message->sizeHint().height()+clientId->sizeHint().height()+accaptButton->sizeHint().height()+4+2*2);
-        button->menu()->setFixedHeight(message->sizeHint().height()+clientId->sizeHint().height()+accaptButton->sizeHint().height()+4+2*2+4);
+/*! Go to firsr friend request */
+void FriendRequestWidget::goFirst()
+{
+    it.toFront();
+    if(it.hasNext()) {
+        it.next();
     }
 }
