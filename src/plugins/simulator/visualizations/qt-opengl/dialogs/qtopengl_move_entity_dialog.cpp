/**
 * @file <argos3/plugins/simulator/visualizations/qt-opengl/dialogs/qtopengl_move_entity_dialog.h>
 *
 * @author Ewout Merckx - <ewoutmerckx.pro@gmail.com>
 */

#include "qtopengl_move_entity_dialog.h"

#include <argos3/core/simulator/loop_functions.h>

#include <QDialogButtonBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QString>
#include <QVBoxLayout>

#include <argos3/core/simulator/entity/floor_entity.h>
//#include <argos3/plugins/robots/e-puck/simulator/epuck_entity.h>
//#include <argos3/plugins/robots/eye-bot/simulator/eyebot_entity.h>
//#include <argos3/plugins/robots/foot-bot/simulator/footbot_entity.h>
//#include <argos3/plugins/robots/spiri/simulator/spiri_entity.h>
#include <argos3/plugins/simulator/entities/box_entity.h>
#include <argos3/plugins/simulator/entities/cylinder_entity.h>
#include <argos3/plugins/simulator/entities/light_entity.h>

namespace argos {

    /****************************************/
    /****************************************/

    CQTOpenGLMoveEntityDialog::CQTOpenGLMoveEntityDialog(QWidget *pc_parent_widget, CQTOpenGLWidget* pc_openglwidget) 
        : QDialog(pc_parent_widget)
    {
        /* Delete the dialog box when closed */
        this->setAttribute(Qt::WA_DeleteOnClose);

        /* Set the widget */
        m_pcOpenGLWidget = pc_openglwidget;

        /* Initialize the layout */
        Init();                            
    }

    /****************************************/
    /****************************************/

    void CQTOpenGLMoveEntityDialog::Init() 
    {
        /* Initialize entity id input field */
        QLabel* pcEntityIdLabel = new QLabel(tr("Entity id"));
        m_pcEntityIdComboBox = new QComboBox;
        std::vector<std::string> vecEntityIds;
        m_pcOpenGLWidget->GetRootEntityIds(vecEntityIds);
        QStringList cEntityIdStringList;
        for(size_t i=0; i<vecEntityIds.size(); i++){
            cEntityIdStringList.append(vecEntityIds[i].c_str());
        } 
        m_pcEntityIdComboBox->addItems(cEntityIdStringList);

        /* Initialize position input fields */
        QLabel* pcEnityPositionXLabel = new QLabel(tr("x"));
        QLabel* pcEnityPositionYLabel = new QLabel(tr("y"));
        QLabel* pcEnityPositionZLabel = new QLabel(tr("z"));
        m_pcEnityPositionXLineEdit = new QLineEdit;
        m_pcEnityPositionYLineEdit = new QLineEdit;
        m_pcEnityPositionZLineEdit = new QLineEdit;
        m_pcEnityPositionXLineEdit->setPlaceholderText("real number");
        m_pcEnityPositionYLineEdit->setPlaceholderText("real number");
        m_pcEnityPositionZLineEdit->setPlaceholderText("real number");

        /* Initialize orientation input fields */
        QLabel* pcEnityOrientationWLabel = new QLabel(tr("w"));
        QLabel* pcEnityOrientationXLabel = new QLabel(tr("x"));
        QLabel* pcEnityOrientationYLabel = new QLabel(tr("y"));
        QLabel* pcEnityOrientationZLabel = new QLabel(tr("z"));
        m_pcEnityOrientationWLineEdit = new QLineEdit;
        m_pcEnityOrientationXLineEdit = new QLineEdit;
        m_pcEnityOrientationYLineEdit = new QLineEdit;
        m_pcEnityOrientationZLineEdit = new QLineEdit;
        m_pcEnityOrientationWLineEdit->setPlaceholderText("real number");
        m_pcEnityOrientationXLineEdit->setPlaceholderText("real number");
        m_pcEnityOrientationYLineEdit->setPlaceholderText("real number");
        m_pcEnityOrientationZLineEdit->setPlaceholderText("real number");

        /* Initialize error label */
        m_pcErrorLabel = new QLabel(tr(""));
        m_pcErrorLabel->setStyleSheet("QLabel { color : red; }");

        /* Initialize buttons */
        QDialogButtonBox* pcMoveDialogButtonBox;
        pcMoveDialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        connect(pcMoveDialogButtonBox, SIGNAL(accepted()), this, SLOT(Accept()));
        connect(pcMoveDialogButtonBox, SIGNAL(rejected()), this, SLOT(Reject()));

        /* Add entity id input field to group box */
        QGroupBox* pcEntityIdGroupBox = new QGroupBox(tr("Entity"));
        QHBoxLayout* pcEntityIdGroupBoxLayout = new QHBoxLayout;
        pcEntityIdGroupBoxLayout->addWidget(pcEntityIdLabel);
        pcEntityIdGroupBoxLayout->addWidget(m_pcEntityIdComboBox);
        pcEntityIdGroupBox->setLayout(pcEntityIdGroupBoxLayout);

        /* Add position input fields to group box */
        QGroupBox* pcEntityPositionGroupBox = new QGroupBox(tr("Position"));
        QHBoxLayout *pcEntityPositionGroupBoxLayout = new QHBoxLayout;
        pcEntityPositionGroupBoxLayout->addWidget(pcEnityPositionXLabel);
        pcEntityPositionGroupBoxLayout->addWidget(m_pcEnityPositionXLineEdit);
        pcEntityPositionGroupBoxLayout->addWidget(pcEnityPositionYLabel);
        pcEntityPositionGroupBoxLayout->addWidget(m_pcEnityPositionYLineEdit);
        pcEntityPositionGroupBoxLayout->addWidget(pcEnityPositionZLabel);
        pcEntityPositionGroupBoxLayout->addWidget(m_pcEnityPositionZLineEdit);
        pcEntityPositionGroupBox->setLayout(pcEntityPositionGroupBoxLayout);

        /* Add orientation input fields to group box */
        QGroupBox* pcEntityOrientationGroupBox = new QGroupBox(tr("Orientation"));
        QHBoxLayout *pcEntityOrientationGroupBoxLayout = new QHBoxLayout;
        pcEntityOrientationGroupBoxLayout->addWidget(pcEnityOrientationWLabel);
        pcEntityOrientationGroupBoxLayout->addWidget(m_pcEnityOrientationWLineEdit);
        pcEntityOrientationGroupBoxLayout->addWidget(pcEnityOrientationXLabel);
        pcEntityOrientationGroupBoxLayout->addWidget(m_pcEnityOrientationXLineEdit);
        pcEntityOrientationGroupBoxLayout->addWidget(pcEnityOrientationYLabel);
        pcEntityOrientationGroupBoxLayout->addWidget(m_pcEnityOrientationYLineEdit);
        pcEntityOrientationGroupBoxLayout->addWidget(pcEnityOrientationZLabel);
        pcEntityOrientationGroupBoxLayout->addWidget(m_pcEnityOrientationZLineEdit);
        pcEntityOrientationGroupBox->setLayout(pcEntityOrientationGroupBoxLayout);

        /* Add group boxes to layout */
        QVBoxLayout* pcDialogLayout = new QVBoxLayout;
        pcDialogLayout->addWidget(pcEntityIdGroupBox);
        pcDialogLayout->addWidget(pcEntityPositionGroupBox);
        pcDialogLayout->addWidget(pcEntityOrientationGroupBox);
        pcDialogLayout->addWidget(m_pcErrorLabel);
        pcDialogLayout->addWidget(pcMoveDialogButtonBox);

        /* Set the title and the layout of the dialog */
        this->setWindowTitle(tr("Move an entity"));
        this->setLayout(pcDialogLayout);
    }

    /****************************************/
    /****************************************/

    void CQTOpenGLMoveEntityDialog::EntitySelectionChanged()
    {
        m_pcErrorLabel->setText(QString(""));
    }

    /****************************************/
    /****************************************/

    void CQTOpenGLMoveEntityDialog::Accept()
    {
        /* Reset error */
        bool bErrorOccured = false;
        m_pcErrorLabel->setText(QString(""));

        /* Get the current selected entity id */
        QString cEntityIdString = m_pcEntityIdComboBox->currentText();
        std::string strEntityId = cEntityIdString.toStdString();

        if(strEntityId != ""){
            /* Get the entity */
            CEntity* cEntity = &m_pcOpenGLWidget->GetEntity(strEntityId);

            /* Create position and orientation with the input values */
            CVector3 cEntityPosition(
                m_pcEnityPositionXLineEdit->text().toDouble(),
                m_pcEnityPositionYLineEdit->text().toDouble(),
                m_pcEnityPositionZLineEdit->text().toDouble()
                );
            CQuaternion cEntityOrientation(
                m_pcEnityOrientationWLineEdit->text().toDouble(),
                m_pcEnityOrientationXLineEdit->text().toDouble(),
                m_pcEnityOrientationYLineEdit->text().toDouble(),
                m_pcEnityOrientationZLineEdit->text().toDouble()
                );

            try{
                /* Get all the entities of the selected type */
                std::string strEntityType = cEntity->GetTypeDescription();
                CSpace::TMapPerType& tEntityMap = 
                    CSimulator::GetInstance().GetLoopFunctions().GetSpace().GetEntitiesByType(strEntityType);

                for(CSpace::TMapPerType::iterator it = tEntityMap.begin();
                    it != tEntityMap.end();
                    ++it) {

                    if(it->first == strEntityId){
                        if(strEntityType == "box"){
                            CBoxEntity& cBoxEnt = *any_cast<CBoxEntity*>(it->second);
                            CSimulator::GetInstance().GetLoopFunctions().MoveEntity(
                                cBoxEnt.GetEmbodiedEntity(), cEntityPosition, cEntityOrientation);
                        }
                        else if(strEntityType == "cylinder") {
                            CCylinderEntity& cCylinderEnt = *any_cast<CCylinderEntity*>(it->second);
                            CSimulator::GetInstance().GetLoopFunctions().MoveEntity(
                                cCylinderEnt.GetEmbodiedEntity(), cEntityPosition, cEntityOrientation);
                        }
                        else if(strEntityType == "e-puck") {
                            //CEPuckEntity& cEPuckEnt = *any_cast<CEPuckEntity*>(it->second);
                            //CSimulator::GetInstance().GetLoopFunctions().MoveEntity(
                            //    cEPuckEnt.GetEmbodiedEntity(), cEntityPosition, cEntityOrientation);
                        }
                        else if(strEntityType == "eye-bot") {
                            //CEyeBotEntity& cEyebotEnt = *any_cast<CEyeBotEntity*>(it->second);
                            //CSimulator::GetInstance().GetLoopFunctions().MoveEntity(
                            //    cEyebotEnt.GetEmbodiedEntity(), cEntityPosition, cEntityOrientation);
                        }
                        else if(strEntityType == "floor") {
                            m_pcErrorLabel->setText(QString("Moving a floor entity is not possible."));
                            bErrorOccured = true;
                        }
                        else if(strEntityType == "foot-bot") {
                            //CFootBotEntity& cFootbotEnt = *any_cast<CFootBotEntity*>(it->second);
                            //CSimulator::GetInstance().GetLoopFunctions().MoveEntity(
                            //    cFootbotEnt.GetEmbodiedEntity(), cEntityPosition, cEntityOrientation);
                        }
                        else if(strEntityType == "light") {
                            CLightEntity& cLightEnt = *any_cast<CLightEntity*>(it->second);
                            CSimulator::GetInstance().GetLoopFunctions().MoveEntity(
                                cLightEnt, cEntityPosition, cEntityOrientation);
                        }
                        else if(strEntityType == "spiri") {
                            //CSpiriEntity& cSpiriEnt = *any_cast<CSpiriEntity*>(it->second);
                            //CSimulator::GetInstance().GetLoopFunctions().MoveEntity(
                            //    cSpiriEnt.GetEmbodiedEntity(), cEntityPosition, cEntityOrientation);
                        }
                        else {
                            m_pcErrorLabel->setText(QString("This type of entity can not yet be moved."));
                            bErrorOccured = true;
                        }
                    }
                }
            }
            catch(CARGoSException& ex) {
                m_pcErrorLabel->setText(QString(ex.what()));
                bErrorOccured = true;
            }
        }

        /* If no error, close the dialog box */
        if(!bErrorOccured){
            //m_pcOpenGLWidget->DrawScene();
            QDialog::close();
        }
    }

    /****************************************/
    /****************************************/

    void CQTOpenGLMoveEntityDialog::Reject()
    {
        /* Close the dialog box */
        QDialog::close();
    }

    /****************************************/
    /****************************************/

}
