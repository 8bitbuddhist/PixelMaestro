#include "cueinterpreter.h"

CueInterpreter::CueInterpreter() { }

std::string CueInterpreter::interpret_cue(uint8_t* cue) {
	// Delegate to the correct handler
	switch ((CueController::Handler)cue[CueController::Byte::PayloadByte]) {
		case CueController::Handler::AnimationHandler:
			return interpret_animation_cue(cue);
			break;
		case CueController::Handler::CanvasHandler:
			return interpret_canvas_cue(cue);
			break;
		case CueController::Handler::MaestroHandler:
			return interpret_maestro_cue(cue);
			break;
		case CueController::Handler::SectionHandler:
			return interpret_section_cue(cue);
			break;
		default:
			return "";
	}
}

std::string CueInterpreter::interpret_animation_cue(uint8_t *cue) {
	std::string result;
	result.append("Section: " + std::to_string(cue[AnimationCueHandler::Byte::SectionByte]));
	result.append(", Overlay: " + std::to_string(cue[AnimationCueHandler::Byte::OverlayByte]));

	switch ((AnimationCueHandler::Action)cue[AnimationCueHandler::Byte::ActionByte]) {
		case AnimationCueHandler::Action::SetColors:
			result.append(", Action: SetColors");
			break;
		case AnimationCueHandler::Action::SetCycleIndex:
			result.append(", Action: SetCycleIndex");
			break;
		case AnimationCueHandler::Action::SetFade:
			result.append(", Action: SetFade");
			break;
		case AnimationCueHandler::Action::SetLightningOptions:
			result.append(", Action: SetLightningOptions");
			break;
		case AnimationCueHandler::Action::SetOrientation:
			result.append(", Action: SetOrientation");
			break;
		case AnimationCueHandler::Action::SetPlasmaOptions:
			result.append(", Action: SetPlasmaOptions");
			break;
		case AnimationCueHandler::Action::SetRadialOptions:
			result.append(", Action: SetRadialOptions");
			break;
		case AnimationCueHandler::Action::SetReverse:
			result.append(", Action: SetReverse");
			break;
		case AnimationCueHandler::Action::SetSparkleOptions:
			result.append(", Action: SetSparkleOptions");
			break;
		case AnimationCueHandler::Action::SetSpeed:
			result.append(", Action: SetSpeed");
			break;
	}

	return result;
}

std::string CueInterpreter::interpret_canvas_cue(uint8_t *cue) {
	std::string result;
	result.append("Section: " + std::to_string(cue[CanvasCueHandler::Byte::SectionByte]));
	result.append(", Overlay: " + std::to_string(cue[CanvasCueHandler::Byte::OverlayByte]));

	result.append(", Canvas Type: ");
	switch((CanvasType::Type)cue[CanvasCueHandler::Byte::TypeByte]) {
		case CanvasType::AnimationCanvas:
			result.append("Animation");
			break;
		case CanvasType::ColorCanvas:
			result.append("Color");
			break;
	}

	switch((CanvasCueHandler::Action)cue[CanvasCueHandler::Byte::ActionByte]) {
		case CanvasCueHandler::Action::DrawCircle:
			result.append(", Action: DrawCircle");
			break;
		case CanvasCueHandler::Action::DrawLine:
			result.append(", Action: DrawLine");
			break;
		case CanvasCueHandler::Action::DrawPoint:
			result.append(", Action: DrawPoint");
			break;
		case CanvasCueHandler::Action::DrawRect:
			result.append(", Action: DrawRect");
			break;
		case CanvasCueHandler::Action::DrawText:
			result.append(", Action: DrawText");
			break;
		case CanvasCueHandler::Action::DrawTriangle:
			result.append(", Action: DrawTriangle");
			break;
		case CanvasCueHandler::Action::NextFrame:
			result.append(", Action: NextFrame");
			break;
		case CanvasCueHandler::Action::SetCurrentFrameIndex:
			result.append(", Action: SetCurrentFrameIndex");
			break;
		case CanvasCueHandler::Action::SetNumFrames:
			result.append(", Action: SetNumFrames");
			break;
		case CanvasCueHandler::Action::SetOffset:
			result.append(", Action: SetOffset");
			break;
		case CanvasCueHandler::Action::SetScroll:
			result.append(", Action: SetScroll");
			break;
	}

	return result;
}

std::string CueInterpreter::interpret_maestro_cue(uint8_t *cue) {
	std::string result = "Maestro ";

	switch((MaestroCueHandler::Action)cue[MaestroCueHandler::Byte::ActionByte]) {
		case MaestroCueHandler::Action::SetRefreshInterval:
			result.append("Action: SetRefreshInterval");
			break;
	}

	return result;
}

std::string CueInterpreter::interpret_section_cue(uint8_t *cue) {
	std::string result;
	result.append("Section: " + std::to_string(cue[CanvasCueHandler::Byte::SectionByte]));
	result.append(", Overlay: " + std::to_string(cue[CanvasCueHandler::Byte::OverlayByte]));

	switch((SectionCueHandler::Action)cue[SectionCueHandler::Byte::ActionByte]) {
		case SectionCueHandler::Action::SetAnimation:
			result.append(", Action: SetAnimation");
			break;
		case SectionCueHandler::Action::SetCanvas:
			result.append(", Action: SetCanvas");
			break;
		case SectionCueHandler::Action::SetDimensions:
			result.append(", Action: SetDimensions");
			break;
		case SectionCueHandler::Action::SetOverlay:
			result.append(", Action: SetOverlay");
			break;
	}

	return result;
}
