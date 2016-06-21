using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ClientDemo
{
    public partial class PTZForm : Form
    {
        public PTZForm()
        {
            InitializeComponent();
        }

 
        private void PTZControl(int nCommand, bool bStop, int nSpeed)
        {
            ClientDemo clientForm = (ClientDemo)this.Owner;
            int nCurVideoform = clientForm.m_nCurIndex;
            if (nCurVideoform >= 0)
            {
                int nPlayHandel = clientForm.m_videoform[nCurVideoform].m_iPlayhandle;
                if (nPlayHandel > 0)
                {
                    int nLoginID = clientForm.m_videoform[nCurVideoform].m_lLogin;
                    int nChannel = clientForm.m_videoform[nCurVideoform].m_iChannel;
                    XMSDK.H264_DVR_PTZControl(nLoginID, nChannel, (int)nCommand, bStop, nSpeed);
                }
            }
        }
        private void buttonUp_MouseDown(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.TILT_UP, false, 4);
        }

        private void buttonUp_MouseUp(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.TILT_UP, true, 4);
        }

        private void buttonUp_MouseLeave(object sender, EventArgs e)
        {
            PTZControl((int)PTZ_ControlType.TILT_UP, true, 4);
        }

        private void buttonDown_MouseDown(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.TILT_DOWN, false, 4);
        }

        private void buttonDown_MouseUp(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.TILT_DOWN, true, 4);
        }

        private void buttonDown_MouseLeave(object sender, EventArgs e)
        {
            PTZControl((int)PTZ_ControlType.TILT_DOWN, true, 4);
        }

        private void buttonLeft_MouseDown(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.PAN_LEFT, false, 4);
        }

        private void buttonLeft_MouseLeave(object sender, EventArgs e)
        {
            PTZControl((int)PTZ_ControlType.PAN_LEFT, true, 4);
        }

        private void buttonLeft_MouseUp(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.PAN_LEFT, true, 4);
        }

        private void buttonRight_MouseDown(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.PAN_RIGHT, false, 4);
        }

        private void buttonRight_MouseLeave(object sender, EventArgs e)
        {
            PTZControl((int)PTZ_ControlType.PAN_RIGHT, true, 4);
        }

        private void buttonRight_MouseUp(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.PAN_RIGHT, true, 4);
        }

        private void buttonMenu_MouseDown(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.EXTPTZ_OPERATION_MENU, false, 0);
        }

        private void buttonMenu_MouseLeave(object sender, EventArgs e)
        {
           // PTZControl((int)PTZ_ControlType.EXTPTZ_OPERATION_MENU, false, 0);
        }

        private void buttonMenu_MouseUp(object sender, MouseEventArgs e)
        {

        }

        private void buttonZoomIn_MouseDown(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.ZOOM_IN, false, 4);
        }

        private void buttonZoomIn_MouseLeave(object sender, EventArgs e)
        {
            PTZControl((int)PTZ_ControlType.ZOOM_IN, true, 4);
        }

        private void buttonZoomIn_MouseUp(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.ZOOM_IN, true, 4);
        }

        private void buttonZoomOut_MouseDown(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.ZOOM_OUT, false, 4);
        }

        private void buttonZoomOut_MouseLeave(object sender, EventArgs e)
        {
            PTZControl((int)PTZ_ControlType.ZOOM_OUT, true, 4);
        }

        private void buttonZoomOut_MouseUp(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.ZOOM_OUT, true, 4);
        }

        private void buttonFocusIn_MouseDown(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.FOCUS_NEAR, false, 4);
        }

        private void buttonFocusIn_MouseLeave(object sender, EventArgs e)
        {
            PTZControl((int)PTZ_ControlType.FOCUS_NEAR, true, 4);
        }

        private void buttonFocusIn_MouseUp(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.FOCUS_NEAR, true, 4);
        }

        private void buttonFocusOut_MouseDown(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.FOCUS_FAR, false, 4);
        }

        private void buttonFocusOut_MouseLeave(object sender, EventArgs e)
        {
            PTZControl((int)PTZ_ControlType.FOCUS_FAR, true, 4);
        }

        private void buttonFocusOut_MouseUp(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.FOCUS_FAR, true, 4);
        }

        private void buttonApertureAdd_MouseDown(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.IRIS_OPEN, false, 4);
        }

        private void buttonApertureAdd_MouseLeave(object sender, EventArgs e)
        {
            PTZControl((int)PTZ_ControlType.IRIS_OPEN, true, 4);
        }

        private void buttonApertureAdd_MouseUp(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.IRIS_OPEN, true, 4);
        }

        private void buttonApertureReduce_MouseDown(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.IRIS_CLOSE, false, 4);
        }

        private void buttonApertureReduce_MouseLeave(object sender, EventArgs e)
        {
            PTZControl((int)PTZ_ControlType.IRIS_CLOSE, true, 4);
        }

        private void buttonApertureReduce_MouseUp(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.IRIS_CLOSE, true, 4);
        }

        private void buttonScanStart_MouseClick(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.EXTPTZ_STARTPANCRUISE, false, 4);
        }

        private void buttonScanStop_MouseClick(object sender, MouseEventArgs e)
        {
            PTZControl((int)PTZ_ControlType.EXTPTZ_STARTPANCRUISE, true, 4);
        }
    }
}