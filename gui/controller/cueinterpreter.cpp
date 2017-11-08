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
			return "No Handler found";
	}
}

std::string CueInterpreter::interpret_animation_cue(uint8_t *cue) {
	std::string result = "Target: Animation, ";
	result.append("Section: " + std::to_string(cue[AnimationCueHandler::Byte::SectionByte]) + ", ");
	result.append("Overlay: " + std::to_string(cue[AnimationCueHandler::Byte::OverlayByte]) + ", ");

	result.append("Action: ");
	switch ((AnimationCueHandler::Action)cue[AnimationCueHandler::Byte::ActionByte]) {
		case AnimationCueHandler::Action::SetColors:
			result.append("SetColors");
			break;
		case AnimationCueHandler::Action::SetCycleIndex:
			result.append("SetCycleIndex");
			break;
		case AnimationCueHandler::Action::SetFade:
			result.append("SetFade");
			break;
		case AnimationCueHandler::Action::SetLightningOptions:
			result.append("SetLightningOptions");
			break;
		case AnimationCueHandler::Action::SetOrientation:
			result.append("SetOrientation");
			break;
		case AnimationCueHandler::Action::SetPlasmaOptions:
			result.append("SetPlasmaOptions");
			break;
		case AnimationCueHandler::Action::SetRadialOptions:
			result.append("SetRadialOptions");
			break;
		case AnimationCueHandler::Action::SetReverse:
			result.append("SetReverse");
			break;
		case AnimationCueHandler::Action::SetSparkleOptions:
			result.append("SetSparkleOptions");
			break;
		case AnimationCueHandler::Action::SetSpeed:
			result.append("SetSpeed");
			break;
		default:
			result.append("Unknown");
			break;
	}

	return result;
}

std::string CueInterpreter::interpret_canvas_cue(uint8_t *cue) {
	std::string result = "Target: Canvas, ";
	result.append("Section: " + std::to_string(cue[CanvasCueHandler::Byte::SectionByte]) + ", ");
	result.append("Overlay: " + std::to_string(cue[CanvasCueHandler::Byte::OverlayByte]) + ", ");

	result.append("Canvas Type: ");
	switch((CanvasType::Type)cue[CanvasCueHandler::Byte::TypeByte]) {
		case CanvasType::AnimationCanvas:
			result.append("Animation, ");
			break;
		case CanvasType::ColorCanvas:
			result.append("Color, ");
			break;
		default:
			result.append("None, ");
			break;
	}

	result.append("Action: ");
	switch((CanvasCueHandler::Action)cue[CanvasCueHandler::Byte::ActionByte]) {
		case CanvasCueHandler::Action::Clear:
			result.append("Clear");
			break;
		case CanvasCueHandler::Action::DrawCircle:
			result.append("DrawCircle");
			break;
		case CanvasCueHandler::Action::DrawFrame:
			result.append("DrawFrame");
			break;
		case CanvasCueHandler::Action::DrawLine:
			result.append("DrawLine");
			break;
		case CanvasCueHandler::Action::DrawPoint:
			result.append("DrawPoint");
			break;
		case CanvasCueHandler::Action::DrawRect:
			result.append("DrawRect");
			break;
		case CanvasCueHandler::Action::DrawText:
			result.append("DrawText");
			break;
		case CanvasCueHandler::Action::DrawTriangle:
			result.append("DrawTriangle");
			break;
		case CanvasCueHandler::Action::NextFrame:
			result.append("NextFrame");
			break;
		case CanvasCueHandler::Action::SetCurrentFrameIndex:
			result.append("SetCurrentFrameIndex");
			break;
		case CanvasCueHandler::Action::SetNumFrames:
			result.append("SetNumFrames");
			break;
		case CanvasCueHandler::Action::SetOffset:
			result.append("SetOffset");
			break;
		case CanvasCueHandler::Action::SetScroll:
			result.append("SetScroll");
			break;
		default:
			result.append("Unknown");
			break;
	}

	return result;
}

std::string CueInterpreter::interpret_maestro_cue(uint8_t *cue) {
	std::string result = "Target: Maestro, Action: ";

	switch((MaestroCueHandler::Action)cue[MaestroCueHandler::Byte::ActionByte]) {
		case MaestroCueHandler::Action::SetRefreshInterval:
			result.append("SetRefreshInterval");
			break;
		default:
			result.append("Unknown");
			break;
	}

	return result;
}

std::string CueInterpreter::interpret_section_cue(uint8_t *cue) {
	std::string result = "Target: Section, ";
	result.append("Section: " + std::to_string(cue[SectionCueHandler::Byte::SectionByte]) + ", ");
	result.append("Overlay: " + std::to_string(cue[SectionCueHandler::Byte::OverlayByte]) + ", ");

	result.append("Action: ");
	switch((SectionCueHandler::Action)cue[SectionCueHandler::Byte::ActionByte]) {
		case SectionCueHandler::Action::RemoveCanvas:
			result.append("RemoveCanvas");
			break;
		case SectionCueHandler::Action::SetAnimation:
			result.append("SetAnimation");
			break;
		case SectionCueHandler::Action::SetCanvas:
			result.append("SetCanvas");
			break;
		case SectionCueHandler::Action::SetDimensions:
			result.append("SetDimensions");
			break;
		case SectionCueHandler::Action::SetOverlay:
			result.append("SetOverlay");
			break;
		default:
			result.append("Unknown");
			break;
	}

	return result;
}
